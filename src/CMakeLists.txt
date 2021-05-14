

# Add source to this project's executable.
add_executable(reconstruction "3DReconstructionKernel.cpp" "cameraInit.cpp" "cameraInit.h"  "featureExtraction.cpp" "featureExtraction.h")
target_link_libraries(reconstruction PUBLIC 
aliceVision_system
	aliceVision_sensorDB
	aliceVision_image
	aliceVision_feature
	aliceVision_sfmData
	aliceVision_sfmDataIO
	Boost::program_options
	Boost::filesystem
	Boost::boost
)
# TODO: Add tests and install targets if needed.
