add_executable(Impi
	"App/Appmain.cpp"
	"../includes/App/Appmain.h"
	"../includes/App/Settings.h"

	"../includes/tools/UserInterface.h"
	"../includes/tools/Logger.h"
	"../includes/tools/Camera.h"
	"../includes/tools/Raycaster.h"
	"../includes/tools/Timer.h"
	"../includes/tools/UserInterface.h"
	"../includes/tools/ViewPort.h"
	

	"../includes/math/Matrix.h"
	"../includes/math/Quaternion.h"
	"../includes/math/random.h"
	"../includes/math/Vector3.h"

	"../includes/opengl/Renderer.h"
	"../includes/opengl/Shader.h"
	"../includes/opengl/Mesh.h"
	"../includes/opengl/LineMesh.h"
	"../includes/opengl/PlaneMesh.h"
	"../includes/opengl/RenderableParticle.h"
	"../includes/opengl/RenderableRigidbody.h"
	"../includes/opengl/SphereParticle.h"
	"../includes/opengl/ViewUniforms.h"

	"../includes/physics/Precision.h"
	"../includes/physics/Objects/Cloth.h"
	"../includes/physics/Objects/Firework.h"
	"../includes/physics/PhysicsWorld.h"

	"../includes/physics/Particle_System/ClothParticle.h"
	"../includes/physics/Particle_System/Constraint.h"
	"../includes/physics/Particle_System/Particle.h"
	"../includes/physics/Particle_System/ParticleContacts.h"
	"../includes/physics/Particle_System/ParticleForceGenerators.h"
	"../includes/physics/Particle_System/ParticleForceRegistry.h"
	"../includes/physics/Particle_System/ParticleLinks.h"
	"../includes/physics/Particle_System/ParticleWorld.h"

	"../includes/physics/Spatial/BoundingVolumes.h"
	"../includes/physics/Spatial/BVHnode.h"
	"../includes/physics/Rigidbody_System/CollisionDetector.h"
	"../includes/physics/Rigidbody_System/CollisionPrimitives.h"
	

	"../includes/physics/Rigidbody_System/Contact.h"
	"../includes/physics/Rigidbody_System/ContactResolver.h"
	"../includes/physics/Rigidbody_System/ForceGenerators.h"
	"../includes/physics/Rigidbody_System/ForceRegistry.h"
	"../includes/physics/Rigidbody_System/IntersectionTests.h"
	"../includes/physics/Rigidbody_System/RigidBody.h"

	"../includes/scenes/Scene.h"
	"../includes/scenes/BoxBoxScene.h"
	"../includes/scenes/ClothScene.h"
	"../includes/scenes/FireWorkScene.h"
	"../includes/scenes/MobileScene.h"
	"../includes/scenes/RopeScene.h"

	"../includes/App/Window.h"

	"App/Appmain.cpp"
	"math/Matrix.cpp"
	"math/Quaternion.cpp"
	"math/random.cpp"
	"math/Vector3.cpp"

	"opengl/CubeMesh.cpp"
	"opengl/LineMesh.cpp"
	"opengl/SphereMesh.cpp"
	"opengl/Shader.cpp"


	"physics/Objects/Cloth.cpp"
	"physics/Objects/Firework.cpp"

	"physics/Particle_System/ClothParticle.cpp"
	"physics/Particle_System/Constraint.cpp"
	"physics/Particle_System/Particle.cpp"
	"physics/Particle_System/ParticleContacts.cpp"
	"physics/Particle_System/ParticleForceGenerators.cpp"
	"physics/Particle_System/ParticleForceRegistry.cpp"
	"physics/Particle_System/ParticleLinks.cpp"
	"physics/Particle_System/ParticleWorld.cpp"

	"physics/Spatial/BoundingSphere.cpp"
	"physics/RigidBody_System/CollisionDetector.cpp"
	"physics/RigidBody_System/Contact.cpp"
	"physics/RigidBody_System/ContactResolver.cpp"
	"physics/RigidBody_System/ForceGenerators.cpp"
	"physics/RigidBody_System/ForceRegistry.cpp"
	"physics/RigidBody_System/IntersectionTests.cpp"
	"physics/RigidBody_System/RigidBody.cpp"

	"scenes/BoxBoxScene.cpp"
	"scenes/ClothScene.cpp"
	"scenes/FireWorkScene.cpp"
	"scenes/MobileScene.cpp"
	"scenes/RopeScene.cpp"
	"scenes/Scene.cpp"

	"tools/Camera.cpp"
	"tools/Logger.cpp"
	"tools/Raycaster.cpp"
	"opengl/Renderer.cpp"

 "physics/PhysicsWorld.cpp")



target_include_directories(Impi
	PRIVATE
		${CMAKE_SOURCE_DIR}/includes
		${CMAKE_SOURCE_DIR}/external/imgui
		${CMAKE_SOURCE_DIR}/external/
	)

target_link_libraries(Impi
	PRIVATE
		glfw
		glad
		imgui
		tinygltf
)

add_custom_command(TARGET Impi POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/shaders
            $<TARGET_FILE_DIR:Impi>/shaders

    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/tex
            $<TARGET_FILE_DIR:Impi>/tex
)
