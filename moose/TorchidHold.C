#include "TorchidHold.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <limits>

registerMooseObject("PorousFlowApp", TorchidHold);

InputParameters
TorchidHold::validParams()
{
  InputParameters params = GeneralUserObject::validParams();
  params.addRequiredParam<Real>("interval", "Time interval between executions (in seconds)");
  params.addParam<Real>("start_time", 0.0, "Time to start executing (in seconds)");
  params.addParam<Real>("end_time", std::numeric_limits<Real>::max(),
                        "Time to stop executing (in seconds)");
  return params;
}

TorchidHold::TorchidHold(const InputParameters & parameters)
  : GeneralUserObject(parameters),
    _interval(getParam<Real>("interval")),
    _start_time(getParam<Real>("start_time")),
    _end_time(getParam<Real>("end_time")),
    _has_end_time(isParamValid("end_time"))
{
}

void
TorchidHold::initialize()
{
}

void
TorchidHold::execute()
{
}

void
TorchidHold::finalize()
{
  Real time = _t; // Current simulation time

  // Skip if outside of time bounds
  if (time < _start_time || (!_has_end_time && time < 0) || time > _end_time)
    return;

  // Check interval: execute only when time aligns with interval
  if (std::fmod(time - _start_time, _interval) > 1e-6)
    return;

  if (processor_id() == 0)
  {
    std::ofstream outputFile("Switch.txt");

    if (outputFile.is_open())
    {
      outputFile << "1" << std::endl;
      outputFile.close();

      std::cout << "[TorchidHold] File 'Switch.txt' written with value '1'."
                << std::endl;
    }
    else
    {
      std::cerr << "[TorchidHold] Error: Could not create 'Switch.txt'."
                << std::endl;
      return;
    }

    while (true)
    {
      std::ifstream inputFile("Switch.txt");

      if (inputFile.is_open())
      {
        std::string switchValue;
        inputFile >> switchValue;
        inputFile.close();

        if (switchValue == "0")
        {
          std::cout << "[TorchidHold] Switch value is 0. Continuing execution."
                    << std::endl;
          break;
        }
        else if (switchValue != "1")
        {
          std::cerr << "[TorchidHold] Error: Invalid value in 'Switch.txt'. "
                       "Exiting loop."
                    << std::endl;
          break;
        }
      }
      else
      {
        std::cerr << "[TorchidHold] Error: Could not open 'Switch.txt' "
                     "for reading. Exiting loop."
                  << std::endl;
        break;
      }
    }

    std::cout << "[TorchidHold] Resuming simulation after wait." << std::endl;
  }
}

Real
TorchidHold::getValue() const
{
  return _output;
}
