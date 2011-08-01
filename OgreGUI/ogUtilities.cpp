#include "StdAfx.h"
#include "ogUtilities.h"

using namespace OgreGUI;

ogUtilities::ogUtilities(void)
{
}

#pragma unmanaged
#include <tchar.h>

#include <windows.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <strsafe.h>
#include <io.h>
#include <fcntl.h>

using namespace std;

ogUtilitiesUM::ogUtilitiesUM(void)
{
}
void ogUtilitiesUM::createConsole(){
	AllocConsole();
	SetConsoleTitle(_T("OgreGui Console"));

	int hConHandle;
	long lStdHandle;
	FILE *fp;

	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stdout = *fp;
	setvbuf( stdout, NULL, _IONBF, 0 );

	// redirect unbuffered STDIN to the console
	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "r" );
	*stdin = *fp;
	setvbuf( stdin, NULL, _IONBF, 0 );

	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stderr = *fp;
	setvbuf( stderr, NULL, _IONBF, 0 );
}
vector<string> ogUtilitiesUM::tokenize(const string& str,const string& delimiters)
{
	vector<string> tokens;
    	
	// skip delimiters at beginning.
    	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    	
	// find first "non-delimiter".
    	string::size_type pos = str.find_first_of(delimiters, lastPos);

    	while (string::npos != pos || string::npos != lastPos)
    	{
        	// found a token, add it to the vector.
        	tokens.push_back(str.substr(lastPos, pos - lastPos));
		
        	// skip delimiters.  Note the "not_of"
        	lastPos = str.find_first_not_of(delimiters, pos);
		
        	// find next "non-delimiter"
        	pos = str.find_first_of(delimiters, lastPos);
    	}

	return tokens;
}

Ogre::SceneNode *ogUtilitiesUM::loadObj(Ogre::SceneManager *mgr,Ogre::String fileName,Ogre::String meshName){
	using namespace Ogre;

	vector<vector<float>> v; 
	vector<vector<int>>	  f;
	int lineCt = 0;
	FILE *stream = fopen(fileName.c_str(), "r");
	if(!stream){
		printf("  - Error, couldn't open obj file %s for reading\n",fileName.c_str());
		return NULL;
	}

	{	///Read obj file
		char buffer[1024];
		vector<string> tokens;

		while(!feof(stream)){
			if(fgets(buffer,1024,stream)==NULL)break;
			tokens = tokenize(buffer," /");
			
			if(tokens.size() > 0){
				remove_if(tokens[0].begin(), tokens[0].end(),isspace);
				char flag = tokens[0][0];
				switch(flag){
					case 'v':
						if(tokens.size() >= 4){
							vector<float> tmp;
							tmp.push_back(atof(tokens[1].c_str()));
							tmp.push_back(atof(tokens[2].c_str()));
							tmp.push_back(atof(tokens[3].c_str()));
							v.push_back(tmp);
						} else {
							printf("  - Warning in line %d, vertex format incorrect.\n",lineCt);
						}
						break;
					case 'f':
						vector<int> tmp;
						if(tokens.size() == 4){
							tmp.push_back(atoi(tokens[1].c_str()));
							tmp.push_back(atoi(tokens[2].c_str()));
							tmp.push_back(atoi(tokens[3].c_str()));
							f.push_back(tmp);
						} else if(tokens.size() == 10){
							tmp.push_back(atoi(tokens[1].c_str()));
							tmp.push_back(atoi(tokens[4].c_str()));
							tmp.push_back(atoi(tokens[7].c_str()));
							f.push_back(tmp);
						} else {
							printf("  - Warning in line %d, face format incorrect.\n",lineCt);
						}
						break;
				};
			} else {
				printf("  - Warning in line %d, string empty\n",lineCt);
			}
			lineCt++;
		}
		printf("  - v.size(): %d\n",v.size());
		printf("  - f.size(): %d\n",f.size());
		fclose(stream);

		{	///Sanity check, make sure the faces index from 0.
			int minF;
			for(int i = 0; i < f.size(); i++){
				for(int k = 0; k < 3; k++){
					if(i==0 && k==0){
						minF = f[i][k];
					} else {
						if(f[i][k] < minF){
							minF = f[i][k];
						}
					}
				}
			}
			if(minF != 0){
				printf("  - Warning, no zero face index found[minF: %d].  Subtracting 1 from all faces\n",minF);
				for(int i = 0; i < f.size(); i++){
					for(int k = 0; k < 3; k++){
						f[i][k] -= 1;
					}
				}
			}
		}
	}	///Done loading obj

	{	///Create manual ogre mesh
		map<int,Vector3> mNormals;
		
		#define VxatF(FACE,VERT) v[f[FACE][VERT]][0]
		#define VyatF(FACE,VERT) v[f[FACE][VERT]][1]
		#define VzatF(FACE,VERT) v[f[FACE][VERT]][2]
		
		//Get Normals
		for(int i = 0; i < f.size(); i++){
			Vector3 ed1 = Vector3(VxatF(i,2),VyatF(i,2),VzatF(i,2)) - 
						  Vector3(VxatF(i,0),VyatF(i,0),VzatF(i,0));
			Vector3 ed2 = Vector3(VxatF(i,1),VyatF(i,1),VzatF(i,1)) - 
						  Vector3(VxatF(i,0),VyatF(i,0),VzatF(i,0));


			Vector3 norm = ed1.crossProduct(ed2);
			norm /= norm.length();
			norm *= -1;

			mNormals[f[i][0]] = norm;
			mNormals[f[i][1]] = norm;
			mNormals[f[i][2]] = norm;
		}
		printf("Complete.\n");

		SceneNode *scene = NULL;
		MeshPtr mesh = MeshManager::getSingleton().createManual(meshName + "_manual_ent","Custom");
		SubMesh *submesh = mesh->createSubMesh();
		printf("       - Mesh/submesh created, populating.\n");

		//Create OgreMesh
		try
		{
			submesh->useSharedVertices = false;
			submesh->vertexData = new VertexData();
			submesh->vertexData->vertexStart = 0;
			submesh->vertexData->vertexCount = v.size() + 1;

			printf("       - Vertex data set up: %d\n",v.size()+1);

			VertexDeclaration * dec = submesh->vertexData->vertexDeclaration;
			static const unsigned short source = 0;
			static const unsigned short csource = 1;		//Color source

			size_t offset;
			HardwareVertexBufferSharedPtr vbuffer;
			AxisAlignedBox aabox;
			{	///Assign vertices
				offset = 0;

				offset += dec->addElement(source,offset,VET_FLOAT3,VES_POSITION).getSize();
				offset += dec->addElement(source,offset,VET_FLOAT3,VES_NORMAL).getSize();

				printf("       - Offsets set: %d\n",offset);
			
				vbuffer = HardwareBufferManager::getSingleton().createVertexBuffer(dec->getVertexSize(source),\
																				   submesh->vertexData->vertexCount,\
																				   HardwareBuffer::HBU_STATIC_WRITE_ONLY);
				printf("       - vbuffer created\n");
				float *vdata = static_cast<float*>(vbuffer->lock(HardwareBuffer::HBL_DISCARD));
				
				printf("       - vdata set\n");
				map<int,Vector3>::const_iterator mIter;

				for(int i = 0; i < v.size(); i++){
					Vector3 pos(v[i][0],v[i][1],v[i][2]);

					*vdata++ = pos.x;
					*vdata++ = pos.y;
					*vdata++ = pos.z;

					Vector3 normal;
					mIter = mNormals.find(i);
					if(mIter != mNormals.end()){
						normal = mNormals[i];
					} else {
						normal = Vector3(1,0,0);
					}
				
					*vdata++ = normal.x;
					*vdata++ = normal.y;
					*vdata++ = normal.z;
					aabox.merge(pos);
				}
				printf("       - vdata populated\n");

				vbuffer->unlock();

				submesh->vertexData->vertexBufferBinding->setBinding(source,vbuffer);
				submesh->indexData->indexStart = 0;
				submesh->indexData->indexCount = f.size() * 3;
				submesh->indexData->indexBuffer = HardwareBufferManager::getSingleton().createIndexBuffer(HardwareIndexBuffer::IT_32BIT,submesh->indexData->indexCount,HardwareBuffer::HBU_STATIC_WRITE_ONLY);
				
				printf("       - index data created\n");

				uint32 *idata = static_cast<uint32*>(submesh->indexData->indexBuffer->lock(HardwareBuffer::HBL_DISCARD));

				for(int i = 0; i < f.size(); i++){
					*idata++ = f[i][0];//face[i].verts[0];
					*idata++ = f[i][1];//face[i].verts[1];
					*idata++ = f[i][2];//face[i].verts[2];
				}
				printf("       - index data populated\n");

				submesh->indexData->indexBuffer->unlock();
			}
			{ ///Assign colour
				printf("  - Assigning Color buffer");
				offset = 0;
				offset += dec->addElement(csource,offset,VET_COLOUR,VES_DIFFUSE).getSize();
				vbuffer = HardwareBufferManager::getSingleton().createVertexBuffer(offset,\
																				   submesh->vertexData->vertexCount,\
																				   HardwareBuffer::HBU_STATIC_WRITE_ONLY);
				RenderSystem *rs = Root::getSingleton().getRenderSystem();
				RGBA *cdata = static_cast<RGBA*>(vbuffer->lock(HardwareBuffer::HBL_DISCARD));
				for(int i = 0; i < f.size(); i++){
					rs->convertColourValue(ColourValue(0.5,0.5,0.5),(cdata+f[i][0]));
					rs->convertColourValue(ColourValue(0.5,0.5,0.5),(cdata+f[i][1]));
					rs->convertColourValue(ColourValue(0.5,0.5,0.5),(cdata+f[i][2]));
				}
				vbuffer->unlock();
				submesh->vertexData->vertexBufferBinding->setBinding(csource,vbuffer);
				printf("Complete.\n");
			}
			mesh->_setBounds(aabox);
			mesh->_setBoundingSphereRadius( (aabox.getMaximum()-aabox.getMinimum()).length() / 2.0);
			
			printf("       - set bounds\n");

			submesh->setMaterialName("Ogre/Generic/CustomColour");
			printf("       - material set\n");

			mesh->load();
			printf("       - loading mesh\n");

			Entity *ent = NULL;
			
			try {
				ent = mgr->getEntity(meshName + "_manual_name");
			} catch (...) {
				ent = mgr->createEntity(meshName + "_manual_name",meshName + "_manual_ent");
			}
			printf("       - entity created\n");
			
			
			try {
				scene = mgr->getSceneNode(meshName + "_manual_node");
			} catch (...) {
				scene = mgr->getRootSceneNode()->createChildSceneNode(meshName + "_manual_node");
			}
			
			printf("       - scenenode created\n");

			ent->setCastShadows(false);
			scene->attachObject(ent);

//			scene->setPosition(drawPos);
			printf("       - scene attached\n");

		}catch (Ogre::Exception& e){
//			MessageBox( NULL, e.getFullDescription().c_str(), "An exception2 has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
		return scene;
	}
	
	return NULL;
}