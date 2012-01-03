#ifndef _CMI8788_H
#define _CMI8788_H

#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>
#include <IOKit/audio/IOAudioDevice.h>
#include <IOKit/audio/IOAudioEngine.h>
#include <IOKit/pci/IOPCIDevice.h>

////////////////////////////////////////////////////////////////////////////////

// Forward decl
class CMI8788AudioEngine;
class CMI8788AudioDevice;

typedef struct CMI8788Registers {
    
} CMI8788Registers;

// Device registers datastruct decl
typedef struct CMI8788DeviceInfo {
    CMI8788Registers *registers;
    IOMemoryMap *deviceMap;
    IOPCIDevice *pciCard;
} CMI8788DeviceInfo;

////////////////////////////////////////////////////////////////////////////////

//! @class CMI8788AudioDevice @interface
class CMI8788AudioDevice : public IOAudioDevice 
{
    OSDeclareDefaultStructors(CMI8788AudioDevice);
    friend class CMI8788AudioEngine;
private:
    //! @typedef
    typedef IOAudioDevice super;
    
    //! @property
    CMI8788DeviceInfo deviceInfo;
    
    //! @method
    bool createAudioEngine();
    
public:
    //! @method
    void free();
    virtual bool initHardware(IOService * provider);
    
    static IOReturn volumeChangeHandler(IOService *target, IOAudioControl *volumeControl, SInt32 oldValue, SInt32 newValue);
    virtual IOReturn volumeChanged(IOAudioControl *volumeControl, SInt32 oldValue, SInt32 newValue);
    
    static IOReturn outputMuteChangeHandler(IOService *target, IOAudioControl *muteControl, SInt32 oldValue, SInt32 newValue);
    virtual IOReturn outputMuteChanged(IOAudioControl *muteControl, SInt32 oldValue, SInt32 newValue);
    
    static IOReturn gainChangeHandler(IOService *target, IOAudioControl *gainControl, SInt32 oldValue, SInt32 newValue);
    virtual IOReturn gainChanged(IOAudioControl *gainControl, SInt32 oldValue, SInt32 newValue);
    
    static IOReturn inputMuteChangeHandler(IOService *target, IOAudioControl *muteControl, SInt32 oldValue, SInt32 newValue);
    virtual IOReturn inputMuteChanged(IOAudioControl *muteControl, SInt32 oldValue, SInt32 newValue);
    
};
// ENDCLASS

////////////////////////////////////////////////////////////////////////////////

//! @class CMI8788AudioEngine @interface
class CMI8788AudioEngine : public IOAudioEngine 
{
    OSDeclareDefaultStructors(CMI8788AudioEngine);
private:
    typedef IOAudioEngine super;
    
public:
    UInt32 getCurrentSampleFrame();
    bool init(CMI8788Registers *registers);
    
};
// ENDCLASS

////////////////////////////////////////////////////////////////////////////////

#endif