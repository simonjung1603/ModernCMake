#pragma once

#include <functional>
#include <memory>
#include "MidiMessage.h"
#include <core_export.h>

namespace mb
{
    //TODO fix macro error
  class __declspec(dllexport) IMidiInputDevice
  {
  public:
    IMidiInputDevice() = default;
    virtual ~IMidiInputDevice() = default;

    virtual void SetMessageCallback(std::function<void(std::shared_ptr<MidiMessage>)> callback) = 0;
    virtual unsigned int GetPortCount() = 0;
    virtual std::string GetPortName(unsigned int portId) = 0;
    virtual void OpenPort(unsigned int portId) = 0;
    virtual void ClosePort() = 0;
  };
}

