// 3DReconstructionTool.cpp : Defines the entry point for the application.

#include "cameraInit.h"
#include "featureExtraction.h"

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include <iostream>
#include <string>
namespace po = boost::program_options;
namespace fs = boost::filesystem;

int main(int argc, char** argv)
{
    std::string sfmFilePath;
    std::string imageFolder;
    std::string sensorDatabasePath;
    std::string cameraInitFilePath;
    po::options_description allParams("AliceVision cameraInit");

    // create the results folder for the intermediate results
    fs::path outputFolder = fs::current_path() /= "data\\intermediate";

    if (!fs::exists(outputFolder))
    {
        if (!fs::create_directory(outputFolder))
        {
            return EXIT_FAILURE;
        }
    }

    cameraInitFilePath = (outputFolder  / "cameraInit.sfm").string();

    po::options_description requiredParams("Required parameters");
    requiredParams.add_options()
        ("input,i", po::value<std::string>(&sfmFilePath)->default_value(sfmFilePath),
            "A SfMData file (*.sfm) [if specified, --imageFolder cannot be used].")
        ("imageFolder", po::value<std::string>(&imageFolder)->default_value(imageFolder),
            "Input images folder [if specified, --input cannot be used].")
        ("sensorDatabase,s", po::value<std::string>(&sensorDatabasePath)->required(),
            "Camera sensor width database path.");
        //("output,o", po::value<std::string>(&outputFilePath)->default_value("cameraInit.sfm"),
        //    "Output file path for the new SfMData file");
    allParams.add(requiredParams);


    po::variables_map vm;
    try
    {
        po::store(po::parse_command_line(argc, argv, allParams), vm);

        if (vm.count("help") || (argc == 1))
        {
            return EXIT_SUCCESS;
        }
        po::notify(vm);
    }
    catch (boost::program_options::required_option& e)
    {
        return EXIT_FAILURE;
    }


    int cameraInit_flag = cameraInit(sfmFilePath, imageFolder, sensorDatabasePath, cameraInitFilePath);
    if (!cameraInit_flag) {
        return EXIT_FAILURE;
    }

    fs::path feature_folder = outputFolder / "feature_extracted";
    int featureExtraction_flag = featureExtraction(cameraInitFilePath, feature_folder.string());
    if (!featureExtraction_flag) {
        return EXIT_FAILURE;
    }

}
