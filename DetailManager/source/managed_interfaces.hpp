#ifndef MANAGED_INTERFACES_HPP
#define MANAGED_INTERFACES_HPP

#include "ats_define.hpp"

using namespace System::Collections;

namespace DetailManager
{
    /// <summary>Vehicle Specification</summary>
    public value class ATS_VEHICLESPEC
    {
    public:
        /// <summary>Number of Brake Notches</summary>
        int BrakeNotches;
        /// <summary>Number of Power Notches</summary>
        int PowerNotches;
        /// <summary>ATS Cancel Notch</summary>
        int AtsNotch;
        /// <summary>80% Brake (67 degree)</summary>
        int B67Notch;
        /// <summary>Number of Cars</summary>
        int Cars;
    };

    /// <summary>State Quantity of Vehicle</summary>
    public value class ATS_VEHICLESTATE
    {
    public:
        /// <summary>Train Position (Z-axis) (m)</summary>
        double Location;
        /// <summary>Train Speed (km/h)</summary>
        float Speed;
        /// <summary>Time (ms)</summary>
        int Time; 
        /// <summary>Pressure of Brake Cylinder (Pa)</summary>
        float BcPressure;
        /// <summary>Pressure of MR (Pa)</summary>
        float MrPressure;
        /// <summary>Pressure of ER (Pa)</summary>
        float ErPressure;
        /// <summary>Pressure of BP (Pa)</summary>
        float BpPressure;
        /// <summary>Pressure of SAP (Pa)</summary>
        float SapPressure;
        /// <summary>Current (A)</summary>
        float Current;
    };

    /// <summary>Received Data from Beacon</summary>
    public value class ATS_BEACONDATA
    {
    public:
        /// <summary>Type of Beacon</summary>
        int Type;
        /// <summary>Signal of Connected Section</summary>
        int Signal;
        /// <summary>Distance to Connected Section (m)</summary>
        float Distance;
        /// <summary>Optional Data</summary>
        int Optional;
    };

    /// <summary>Train Operation Instruction</summary>
    public value class ATS_HANDLES
    {
    public:
        /// <summary>Brake Notch</summary>
        int Brake;
        /// <summary>Power Notch</summary>
        int Power;
        /// <summary>Reverser Position</summary>
        int Reverser;
        /// <summary>Constant Speed Control</summary>
        int ConstantSpeed;
    };

    public ref class NativeIntArray
    {
    private:
        int* p_array;

    public:
        NativeIntArray(int* arg_p_array) {
            p_array = arg_p_array;
        }

        property int Length{
            int get() {
                return 256;
            }
        }

        property int default[int]{
            int get(int index) {
                return p_array[index];
            }
            void set(int index, int value) {
                p_array[index] = value;
            }
        }
    };

    public interface class IMinimumATSPlugin
    {
        int GetPluginVersion();
    };

    /// <summary>Defines that the Load function is implemented</summary>
    public interface class IATSLoad : IMinimumATSPlugin
    {
        void Load();
    };

    public interface class IATSDispose : IMinimumATSPlugin, System::IDisposable {};

    public interface class IATSGetPluginVersion : IMinimumATSPlugin {};

    public interface class IATSSetVehicleSpec : IMinimumATSPlugin
    {
        void SetVehicleSpec(ATS_VEHICLESPEC vspec);
    };

    public interface class IATSInitialize : IMinimumATSPlugin
    {
        void Initialize(int param);
    };

    public interface class IATSElapse : IMinimumATSPlugin
    {
        ATS_HANDLES Elapse(ATS_VEHICLESTATE vs, NativeIntArray p_panel, NativeIntArray p_sound);
    };

    public interface class IATSSetPower : IMinimumATSPlugin
    {
        void SetPower(int notch);
    };

    public interface class IATSSetBrake : IMinimumATSPlugin
    {
        void SetBrake(int notch);
    };

    public interface class IATSSetReverser : IMinimumATSPlugin
    {
        void SetReverser(int pos);
    };

    public interface class IATSKeyDown : IMinimumATSPlugin
    {
        void KeyDown(int ats_key_code);
    };

    public interface class IATSKeyUp : IMinimumATSPlugin
    {
        void KeyUp(int ats_key_code);
    };

    public interface class IATSHornBrow : IMinimumATSPlugin
    {
        void HornBrow(int ats_horn);
    };

    public interface class IATSDoorOpen : IMinimumATSPlugin
    {
        void DoorOpen();
    };

    public interface class IATSDoorClose : IMinimumATSPlugin
    {
        void DoorClose();
    };

    public interface class IATSSetSignal : IMinimumATSPlugin
    {
        void SetSignal(int signal);
    };

    public interface class IATSSetBeaconData : IMinimumATSPlugin
    {
        void SetBeaconData(ATS_BEACONDATA beacon_data);
    };

    public interface class IFullFuncATSPlugin
        : IMinimumATSPlugin,
        IATSLoad,
        IATSDispose,
        IATSGetPluginVersion,
        IATSSetVehicleSpec,
        IATSInitialize,
        IATSElapse,
        IATSSetPower,
        IATSSetBrake,
        IATSSetReverser,
        IATSKeyDown,
        IATSKeyUp,
        IATSHornBrow,
        IATSDoorOpen,
        IATSDoorClose,
        IATSSetSignal,
        IATSSetBeaconData {};
}

#endif // MANAGED_INTERFACES_HPP