#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>
#include "Particle.h"
#include "Plane.h"
#include "Projectile.h"
#include "ParticleSystem.h"
#include "SimpleParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "WaterDropParticle.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "WindAreaForceGenerator.h"
#include "TornadoAreaForceGenerator.h"
#include "BallParticle.h"
#include "ExplosionForceGenerator.h"
#include "ExplosionExpandingForceGenerator.h"
#include "BuoyancyForceGenerator.h"



using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

// ---

Plane* plane;
std::vector<Projectile*> projectiles;

ParticleSystem* partSystem;
ParticleGenerator* currentGen;
Particle* currentParticle;

std::vector<ExplosionForceGenerator*> explosionFs;
ExplosionForceGenerator* explosionFAux;
WindAreaForceGenerator* windF;
TornadoAreaForceGenerator* tornadoF;

Particle* springExParticle;
Particle* springPart2;
Particle* springPart1;

BuoyancyForceGenerator* buoyF;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	plane = new Plane(Vector3(0, -3, 0));

	partSystem = new ParticleSystem();

	// Fuente
	//// currentGen = new SimpleParticleGenerator(Vector3(0, 2, -10), Vector3(0, 25, 0), Vector3(0, -10, 0), 3.5, Vector3(2, 0, 2), Vector3(5, 2, 5), 0.5, 2);
	////currentGen = new SimpleParticleGenerator(Vector3(0, 2, -10), Vector3(0, 25, 0), Vector3(0, 0, 0), 3.5, Vector3(2, 0, 2), Vector3(5, 2, 5), 0.5, 2);
	//currentGen->setParticle(new WaterDropParticle(0.5, 2.0));
	/*partSystem->setGenerator(currentGen);*/

	partSystem->generateFireworkSystem();

	GravityForceGenerator* gravF = new GravityForceGenerator(Vector3(0, -10, 0));
	partSystem->addForceGen(gravF);

	//// Spring Example/s
	//Vector3 anchor = { 0, 30, -10 };
	//springExParticle = new Particle({ 8, 20, -18 }, { 0, 0, 0 }, { 0, 0, 0 }, 0.998, 2, -1, { 1, 1, 0, 1 }, 2);
	//springExParticle->setResets(false);

	//partSystem->createAnchoredSpring(springExParticle, anchor, 15, 10);
	//partSystem->addToPartFRegistry(springExParticle, gravF);

}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	plane->update(t);
	partSystem->update(t);

	for (int i = 0; i < projectiles.size(); i++) {
		projectiles[i]->update(t);
		if (!projectiles[i]->getAlive()) {
			Projectile* p = projectiles[i];
			projectiles.erase(projectiles.begin() + i);
			delete p;
		}
	}

	for (int i = 0; i < explosionFs.size(); i++)
	{
		explosionFs[i]->updateGenerator(t);
		if (explosionFs[i]->getTimeSinceActivation() > 2.0) {
			partSystem->removeForceGen(explosionFs[i]);
		}
	}

}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

	delete plane;

	delete partSystem;

	for (auto p : projectiles) {
		delete p;
	}

	// delete springExParticle;
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case ' ':
	{
		Vector3 front = camera.q.getBasisVector2().getNormalized();
		// E = 3721
		// 1220 m/s, 5g, con g = -9.8m/s2
		// a 60 m/s, 2067g (2kg) con g = -0.482m/s2
		projectiles.push_back(new Projectile(camera.p + Vector3(0, -1, 0), front * -60, Vector3(0, -0.482, 0), 0.998, 2.067));
		break;
	}
	case '1':
		if (currentGen != nullptr) {
			delete currentGen;
			currentGen = nullptr;
		}
		partSystem->resetParticles();
		currentGen = new SimpleParticleGenerator(Vector3(0, 2, -10), Vector3(0, 25, 0), Vector3(0, 0, 0), 3.5, Vector3(2, 0, 2), Vector3(5, 2, 5), 0.5, 0.5);
		currentParticle = new WaterDropParticle(0.5, 0.5);
		currentGen->setParticle(currentParticle);
		partSystem->setGenerator(currentGen);
		break;

	case '2':
		if (currentGen != nullptr) {
			delete currentGen;
			currentGen = nullptr;
		}
		partSystem->resetParticles();
		currentGen = new GaussianParticleGenerator(Vector3(0, 2, -10), Vector3(0, 25, 0), 3.5, Vector3(0.5, 0.2, 0.5), Vector3(1.25, 0.5, 1.25), 0.5);
		currentParticle = new WaterDropParticle(0.5, 0.5);
		currentGen->setParticle(currentParticle);
		partSystem->setGenerator(currentGen);
		break;

	case '3':
		if (currentGen != nullptr) {
			delete currentGen;
			currentGen = nullptr;
		}
		partSystem->resetParticles();
		currentGen = new SimpleParticleGenerator(Vector3(0, 20, -10), Vector3(0, 0, 0), Vector3(0, 0, 0), 3.5, Vector3(5, 0, 5), Vector3(10, 5, 10), 0.5, 0.5);
		currentParticle = new WaterDropParticle(0.5, 0.5);
		currentGen->setParticle(currentParticle);
		partSystem->setGenerator(currentGen);
		break;

	case '4':
		if (currentGen != nullptr) {
			delete currentGen;
			currentGen = nullptr;
		}
		partSystem->resetParticles();
		currentGen = new GaussianParticleGenerator(Vector3(0, 20, -10), Vector3(0, 0, 0), 3.5, Vector3(1.25, 0.2, 1.25), Vector3(2.5, 1.25, 2.5), 0.5);
		currentParticle = new WaterDropParticle(0.5, 0.5);
		currentGen->setParticle(currentParticle);
		partSystem->setGenerator(currentGen);
		break;

	case '5':
		if (currentGen != nullptr) {
			delete currentGen;
			currentGen = nullptr;
		}
		partSystem->resetParticles();
		partSystem->generateFirework(2, Vector3(0, 2, -10), Vector3(0, 25, 0));
		partSystem->setGenerator(currentGen);
		break;

	case '6':
		if (currentGen != nullptr) {
			delete currentGen;
			currentGen = nullptr;
		}
		partSystem->resetParticles();
		currentGen = new GaussianParticleGenerator(Vector3(0, 20, -10), Vector3(0, 0, 0), 5, Vector3(3, 0.5, 3), Vector3(2.5, 1.25, 2.5), 0.5);
		currentParticle = new BallParticle(2, 2);
		currentGen->setParticle(currentParticle);
		partSystem->setGenerator(currentGen);
		break;

	case '7':
		if (windF == nullptr) {
			windF = new WindAreaForceGenerator(Vector3(0, 20, 0), Vector3(0, 0, -10), Vector3(50, 20, 50));
			partSystem->addForceGen(windF);
		}
		else {
			partSystem->removeForceGen(windF);
			windF = nullptr;
		}
		break;

	case '8':
		if (tornadoF == nullptr) {
			tornadoF = new TornadoAreaForceGenerator(2, Vector3(0, 0, -10), Vector3(20, 20, 20));
			partSystem->addForceGen(tornadoF);
		}
		else {
			partSystem->removeForceGen(tornadoF);
			tornadoF = nullptr;
		}
		break;

	case '9':
		explosionFAux = new ExplosionForceGenerator(Vector3(0, 15, -10), 50.0, 100000.0, 0.1);
		explosionFs.push_back(explosionFAux);
		partSystem->addForceGen(explosionFAux);
		break;
		
	/*case '0':
		explosionFAux = new ExplosionExpandingForceGenerator(Vector3(0, 15, -10), 50.0, 100000.0, 0.1, 2.0);
		explosionFs.push_back(explosionFAux);
		partSystem->addForceGen(explosionFAux);
		break;*/

	case '0':
		if (currentGen != nullptr) {
			delete currentGen;
			currentGen = nullptr;
		}
		partSystem->resetParticles();
		partSystem->setGenerator(currentGen);
		break;
		
	case 'Q':
		if (currentGen != nullptr) {
			delete currentGen;
			currentGen = nullptr;
		}
		partSystem->resetParticles();
		partSystem->setGenerator(currentGen);

		springPart1 = new Particle({ 8, 20, -18 }, { 0, 0, 0 }, { 0, 0, 0 }, 0.998, 2, -1, { 0, 1, 1, 1 }, 2);
		springPart2 = new Particle({ 18, 20, -10 }, { 0, 0, 0 }, { 0, 0, 0 }, 0.998, 2, -1, { 0, 1, 1, 1 }, 2);
		springPart1->setResets(false);
		springPart2->setResets(false);

		partSystem->createSpring(springPart1, springPart2, 25, 10);
		break;
		
	case 'E':
		if (currentGen != nullptr) {
			delete currentGen;
			currentGen = nullptr;
		}
		partSystem->resetParticles();
		partSystem->setGenerator(currentGen);

		partSystem->createSlinky(5, 5, 100, new Particle({ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 0.998, 2, -1, { 0, 1, 1, 1 }, 2), { 10, 100, -10});
		break;
		
	case 'R':
		if (buoyF == nullptr) {
			buoyF = new BuoyancyForceGenerator(12, 0.001, 1000);
			partSystem->addForceGen(buoyF);
		}
		else {
			partSystem->removeForceGen(buoyF);
			buoyF = nullptr;
		}
		break;

	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}