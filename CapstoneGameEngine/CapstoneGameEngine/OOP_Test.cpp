//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Copyright (c) 2008-2022 NVIDIA Corporation. All rights reserved.
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  
//
// ****************************************************************************
// This snippet illustrates simple use of physx
//
// It creates a number of box stacks on a plane, and if rendering, allows the
// user to create new stacks and fire a ball from the camera position
// ****************************************************************************
//
//#include <ctype.h>
//#include <vector>
//#include "External/PhysX/include/PxPhysics.h"
//#include "External/PhysX/include/PxPhysicsAPI.h"
//#include "External/PhysX/include/foundation/PxPreprocessor.h"
//#include "External/PhysX/snippets/snippetrender/SnippetRender.h"
//#include "External/PhysX/snippets/snippetrender/SnippetCamera.h"
//#include "External/PhysX/snippets/snippetutils/SnippetUtils.h"
//
//#include <glew.h>
//#include <iostream>
//#include <SDL.h>
//#include "Debug.h"
//#include "OOP_Test.h"
//#include "MMath.h"
//#include "QMath.h"
//#include "Timer.h"
//#include "Debug.h"
//#include <array>
//
//std::unordered_map<std::string, Ref<Actor>> actorContainer;
//std::unordered_map<std::string, Ref<Actor >> getAllActors() { return actorContainer; }
//
//template<typename ActorTemplate>
//void AddActor(std::string name, Ref<Actor> parent_, Ref<ActorTemplate> actor_) {
//	if (dynamic_cast<Actor*>(actor_.get())) {
//		if (Ref<TransformComponent> tc = actor_->GetComponent<TransformComponent>()) {
//			tc->SetParent(parent_);
//		}
//	}
//	actorContainer[name] = actor_;
//}
//
//template<typename ActorTemplate>
//Ref<ActorTemplate> GetActor(std::string name) {
//	auto id = actorContainer.find(name);
//#ifdef _DEBUG
//	if (id == actorContainer.end()) {
//		Debug::Error("Can't find requested actor", __FILE__, __LINE__);
//		return Ref<ActorTemplate>(nullptr);
//	}
//#endif
//	return std::dynamic_pointer_cast<ActorTemplate>(id->second);
//}
//
//std::vector<std::shared_ptr<int>> physxIDs;
//std::unordered_map<const char*, float> UpdateProfiling;
//
//float globalTime;
//void globalEntityUpdate(float deltaTime) {
//	UpdateProfiling.insert(std::pair<const char*, float>("SinUpdate", 0.0f));
//	ProfilingTimer character("SinUpdate", &UpdateProfiling);
//	for (auto actor : getAllActors())
//	{
//		actor.second->GetComponent<TransformComponent>()->SetPosition(Vec3(actor.second->GetComponent<TransformComponent>()->GetPosition().x, actor.second->GetComponent<TransformComponent>()->GetPosition().y + sin(globalTime), actor.second->GetComponent<TransformComponent>()->GetPosition().z));
//		printf("%s- x: %f y: %f\n", actor.first.c_str(), actor.second->GetComponent<TransformComponent>()->GetPosition().x, actor.second->GetComponent<TransformComponent>()->GetPosition().y);
//	}
//	globalTime += deltaTime;
//	printf("%f\n", globalTime);
//}
//
//using namespace physx;
//
//static PxDefaultAllocator		gAllocator;
//static PxDefaultErrorCallback	gErrorCallback;
//static PxFoundation* gFoundation = NULL;
//static PxPhysics* gPhysics = NULL;
//static PxDefaultCpuDispatcher* gDispatcher = NULL;
//static PxScene* gScene = NULL;
//static PxMaterial* gMaterial = NULL;
//static PxPvd* gPvd = NULL;
//
//static PxReal stackZ = 10.0f;
//
//static PxRigidDynamic* createDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity = PxVec3(0))
//{
//	PxRigidDynamic* dynamic = PxCreateDynamic(*gPhysics, t, geometry, *gMaterial, 10.0f);
//	dynamic->setAngularDamping(0.5f);
//	dynamic->setLinearVelocity(velocity);
//	gScene->addActor(*dynamic);
//	return dynamic;
//}
//
//static void createStack(const PxTransform& t, PxU32 size, PxReal halfExtent)
//{
//	PxShape* shape = gPhysics->createShape(PxBoxGeometry(halfExtent, halfExtent, halfExtent), *gMaterial);
//	for (PxU32 i = 0; i < size; i++)
//	{
//		for (PxU32 j = 0; j < size - i; j++)
//		{
//			PxTransform localTm(PxVec3(PxReal(j * 2) - PxReal(size - i), PxReal(i * 2 + 1), 0) * halfExtent);
//			PxRigidDynamic* body = gPhysics->createRigidDynamic(t.transform(localTm));
//			body->attachShape(*shape);
//			PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
//			gScene->addActor(*body);
//		}
//	}
//	shape->release();
//}
//
//void initPhysics(bool interactive)
//{
//	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
//
//	/*gPvd = PxCreatePvd(*gFoundation);
//	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
//	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);*/
//
//	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);
//
//	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
//	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
//	gDispatcher = PxDefaultCpuDispatcherCreate(2);
//	sceneDesc.cpuDispatcher = gDispatcher;
//	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
//	gScene = gPhysics->createScene(sceneDesc);
//
//	PxPvdSceneClient* pvdClient = gScene->getScenePvdClient();
//	if (pvdClient)
//	{
//		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
//		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
//		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
//	}
//	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
//
//	PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0, 1, 0, 0), *gMaterial);
//	gScene->addActor(*groundPlane);
//
//	for (PxU32 i = 0; i < 5; i++)
//		createStack(PxTransform(PxVec3(0, 0, stackZ -= 10.0f)), 10, 2.0f);
//
//	if (!interactive)
//		createDynamic(PxTransform(PxVec3(0, 40, 100)), PxSphereGeometry(10), PxVec3(0, -50, -100));
//
//	for (int i = 0; i < 10; i++)
//	{
//		PxShape* shape = gPhysics->createShape(PxBoxGeometry(1.0f, 1.0f, 1.0f), *gMaterial);
//		PxTransform localTm(PxVec3(PxReal(0), PxReal(i * 3), 10) * 1.0f);
//		PxRigidDynamic* body = gPhysics->createRigidDynamic(localTm);
//		body->attachShape(*shape);
//		PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
//		gScene->addActor(*body);
//
//		shape->release();
//
//		AddActor("Object" + std::to_string(i), nullptr, std::make_shared<Actor>(nullptr));
//		GetActor<Actor>("Object" + std::to_string(i))->AddComponent<TransformComponent>(nullptr);
//		physxIDs.push_back(std::make_shared<int>());
//		body->userData = physxIDs[physxIDs.size() - 1].get();
//		GetActor<Actor>("Object" + std::to_string(i))->GetComponent<TransformComponent>()->physxID = physxIDs[physxIDs.size() - 1].get();
//	}
//}
//
//void stepPhysics(bool /*interactive*/)
//{
//	UpdateProfiling.insert(std::pair<const char*, float>("StepPhysics", 0.0f));
//	ProfilingTimer character("StepPhysics", &UpdateProfiling);
//	
//	std::array<PxActor*, 1000> actors;
//	PxU32 numActors = 0;
//	numActors = gScene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC, actors.data(), 1000, 0);
//
//	globalEntityUpdate(1.0f / 60.0f);
//
//	for (int i = 0; i < numActors; i++)
//	{
//		auto rigidBody = static_cast<PxRigidDynamic*>(actors[i]);
//		if (rigidBody)
//		{
//			for (auto e : getAllActors()) {
//				if (rigidBody->userData == e.second->GetComponent<TransformComponent>()->physxID)
//				{
//					Vec3 position = e.second->GetComponent<TransformComponent>()->GetPosition();
//					Quaternion orientation = e.second->GetComponent<TransformComponent>()->getOrientation();
//					PxTransform transform = PxTransform(position.x, position.y, position.z, PxQuat(orientation.ijk.x, orientation.ijk.y, orientation.ijk.z, orientation.w));
//					static_cast<PxRigidDynamic*>(actors[i])->setGlobalPose(transform);
//				}
//			}
//		}
//	}
//
//	gScene->simulate(1.0f / 60.0f);
//	gScene->fetchResults(true);
//
//	for (int i = 0; i < numActors; i++)
//	{
//		auto rigidBody = static_cast<PxRigidDynamic*>(actors[i]);
//		if (rigidBody)
//		{
//			for (auto e : getAllActors()) {
//				if (rigidBody->userData == e.second->GetComponent<TransformComponent>()->physxID)
//				{
//					Vec3 pos;
//					pos.x = static_cast<PxRigidDynamic*>(actors[i])->getGlobalPose().p.x;
//					pos.y = static_cast<PxRigidDynamic*>(actors[i])->getGlobalPose().p.y;
//					pos.z = static_cast<PxRigidDynamic*>(actors[i])->getGlobalPose().p.z;
//					PxQuat orientation = static_cast<PxRigidDynamic*>(actors[i])->getGlobalPose().q;
//					e.second->GetComponent<TransformComponent>()->SetTransform(pos, Quaternion(orientation.w, orientation.x, orientation.y, orientation.z));
//				}
//			}
//		}
//	}
//}
//
//void cleanupPhysics(bool /*interactive*/)
//{
//	PX_RELEASE(gScene);
//	PX_RELEASE(gDispatcher);
//	PX_RELEASE(gPhysics);
//	if (gPvd)
//	{
//		PxPvdTransport* transport = gPvd->getTransport();
//		gPvd->release();	gPvd = NULL;
//		PX_RELEASE(transport);
//	}
//	PX_RELEASE(gFoundation);
//
//	printf("SnippetHelloWorld done.\n");
//}
//
//void keyPress(unsigned char key, const PxTransform& camera)
//{
//	switch (toupper(key))
//	{
//	case 'B':	createStack(PxTransform(PxVec3(0, 0, stackZ -= 10.0f)), 10, 2.0f);						break;
//	case ' ':	createDynamic(camera, PxSphereGeometry(3.0f), camera.rotate(PxVec3(0, 0, -1)) * 200);	break;
//	}
//}
//
//int snippetMain()
//{
//	extern void renderLoop();
//	renderLoop();
//
//	return 0;
//}
//
//extern void initPhysics(bool interactive);
//extern void stepPhysics(bool interactive);
//extern void cleanupPhysics(bool interactive);
//extern void keyPress(unsigned char key, const PxTransform& camera);
//
//Snippets::Camera* sCamera;
//
//void renderCallback()
//{
//	stepPhysics(true);
//
//	Snippets::startRender(sCamera);
//
//	PxScene* scene;
//	PxGetPhysics().getScenes(&scene, 1);
//	PxU32 nbActors = scene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);
//	if (nbActors)
//	{
//		std::vector<PxRigidActor*> actors(nbActors);
//		scene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC, reinterpret_cast<PxActor**>(&actors[0]), nbActors);
//		Snippets::renderActors(&actors[0], static_cast<PxU32>(actors.size()), true);
//	}
//
//	Snippets::finishRender();
//}
//
//void exitCallback(void)
//{
//	delete sCamera;
//	cleanupPhysics(true);
//
//	for (auto u : UpdateProfiling)
//	{
//		std::cout << std::endl << "Total time in ms spent in: " << u.first << " " << u.second << std::endl;
//	}
//}
//
//void renderLoop()
//{
//	sCamera = new Snippets::Camera(PxVec3(50.0f, 50.0f, 50.0f), PxVec3(-0.6f, -0.2f, -0.7f));
//
//	Snippets::setupDefault("PhysX Snippet HelloWorld", sCamera, keyPress, renderCallback, exitCallback);
//
//	initPhysics(true);
//	glutMainLoop();
//}
//
//OOP_Test::OOP_Test() {
//	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
//}
//
//OOP_Test::~OOP_Test() {
//	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
//	OnDestroy();
//}
//
//bool OOP_Test::OnCreate() {
//	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);
//
//	/*for (int i = 0; i < 10; i++)
//	{
//		makeObject(registry);
//		makeLight(registry);
//	}*/
//
//	snippetMain();
//
//	return true;
//}
//
//void OOP_Test::OnDestroy() {
//	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);
//}
//
//void OOP_Test::HandleEvents(const SDL_Event& sdlEvent) {
//
//}
//
//void OOP_Test::Update(const float deltaTime) {
//	time += deltaTime;
//	
//	printf("\n");
//}
//
//void OOP_Test::Render() const {
//
//}
//
//
