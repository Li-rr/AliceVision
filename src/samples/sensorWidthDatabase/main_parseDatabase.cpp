// This file is part of the AliceVision project and is made available under
// the terms of the MPL2 license (see the COPYING.md file).

#include "dependencies/cmdLine/cmdLine.h"

#include "aliceVision/exif/sensor_width_database/ParseDatabase.hpp"

int main(int argc, char ** argv)
{
  CmdLine cmd;
  std::cout << argc << std::endl;
  std::string sfileDatabase;
  std::string sBrand;
  std::string sModel;

  cmd.add( make_option('i', sfileDatabase, "ifileDB") );
  cmd.add( make_option('b', sBrand, "iBrand") );
  cmd.add( make_option('m', sModel, "iModel") );

  try {
      if (argc == 1) throw std::string("Invalid command line parameter.");
      cmd.process(argc, argv);
  } catch(const std::string& s) {
      std::cerr << "Look if the given references exist in the camera database file.\nUsage: " << argv[0] << ' '
      << "[-i|--DatabaseFile path] "
      << "[-b|--Brand ] "
      << "[-m|--Model] "
      << std::endl;

      std::cerr << s << std::endl;
      return EXIT_FAILURE;
  }
  std::cout << " You called : " <<std::endl
            << argv[0] << std::endl
            << "--DatabaseFile " << sfileDatabase << std::endl
            << "--Brand " << sBrand << std::endl
            << "--Model " << sModel << std::endl;

  std::vector<aliceVision::exif::sensordb::Datasheet> vec_database;
  aliceVision::exif::sensordb::Datasheet datasheet;

  if ( !aliceVision::exif::sensordb::parseDatabase( sfileDatabase, vec_database ) )
  {
    std::cout << "Database creation failure from the file : " << sfileDatabase  << std::endl;
    return EXIT_FAILURE;
  }

  if ( !aliceVision::exif::sensordb::getInfo( sBrand, sModel, vec_database, datasheet ) )
  {
    std::cout << "The camera " << sModel << " doesn't exist in the database" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Result : " << std::endl << datasheet._brand << "\t" << datasheet._model << "\t" << datasheet._sensorSize << std::endl;

  return EXIT_SUCCESS;
}

