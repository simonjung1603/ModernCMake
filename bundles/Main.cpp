#ifdef _WIN32
#pragma warning( push )
#pragma warning( disable : 4251 )
#endif
#include <cppmicroservices/Framework.h>
#include <cppmicroservices/FrameworkFactory.h>
#include <cppmicroservices/BundleContext.h>
#include "IMidiInputDevice.h"
#ifdef _WIN32
#pragma warning( pop )
#endif

int main(int argc, char* argv[])
{
    US_UNUSED(argc);
    US_UNUSED(argv);
    try
    {
        auto factory = cppmicroservices::FrameworkFactory();
        auto framework = factory.NewFramework();
        framework.Init();

        auto context = framework.GetBundleContext();
        //TODO replace by macro
        context.InstallBundles("E:/Programming/MidiBuddy_bin/MidiBuddyBuild/bin/midi.dll");
        //BundleInstaller::InstallAllBundles(context);

        framework.Start();
        for (auto bundle : context.GetBundles())
        {
            bundle.Start();
        }

        auto ctx = framework.GetBundleContext();

        auto MidiInServiceRef = ctx.GetServiceReference<mb::IMidiInputDevice>();
        auto MidiInService = MidiInServiceRef ? ctx.GetService(MidiInServiceRef) : nullptr;
        if(MidiInService)
        {
            std::cout << "Found MidiInService!\n";
            std::cout << "Found " << MidiInService->GetPortCount()<< " ports.\n";
            for(auto i = 0u; i < MidiInService->GetPortCount(); ++i)
            {
                std::cout << i << ":\t" << MidiInService->GetPortName(i) << '\n';
            }
        }else
        {
            std::cout << "No MidiInService present.\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << "'\n";
    }
}

