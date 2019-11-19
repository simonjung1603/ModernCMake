#include "MidiBundleActivator.h"

#include <memory>
#include "RtMidiInAdapter.h"

void MidiBundleActivator::Start(cppmicroservices::BundleContext context)
{
    auto midiInService = std::make_shared<mb::RtMidiInAdapter>();
    auto midiInServiceRegistration = context.RegisterService<mb::IMidiInputDevice>(midiInService);
    m_MidiInServiceInfo = { midiInService, midiInServiceRegistration };

}

void MidiBundleActivator::Stop(cppmicroservices::BundleContext context)
{
}
