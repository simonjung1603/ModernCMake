#pragma once

#ifdef _WIN32
#pragma warning( push )
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )
#endif
#include <cppmicroservices/BundleActivator.h>

#include <midi_export.h>
#include "RtMidiInAdapter.h"

class MIDI_EXPORT MidiBundleActivator : public cppmicroservices::BundleActivator
{
public:
    MidiBundleActivator() = default;
    void Start(cppmicroservices::BundleContext context) override;
    void Stop(cppmicroservices::BundleContext context) override;
    std::pair<std::shared_ptr<mb::RtMidiInAdapter>, cppmicroservices::ServiceRegistration<mb::IMidiInputDevice>> m_MidiInServiceInfo;
};

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(MidiBundleActivator)

#ifdef _WIN32
#pragma warning( pop )
#endif
