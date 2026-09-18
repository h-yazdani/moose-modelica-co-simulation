#pragma once

#include "GeneralUserObject.h"

/**
 * Pauses MOOSE execution based on an external file signal.
 */
class TorchidHold : public GeneralUserObject
{
public:
  static InputParameters validParams();

  TorchidHold(const InputParameters & parameters);

  virtual void initialize() override;
  virtual void execute() override;
  virtual void finalize() override;
  virtual Real getValue() const;

protected:
  int _output;

  // Time-based execution control
  Real _interval;
  Real _start_time;
  Real _end_time;
  bool _has_end_time;
};
