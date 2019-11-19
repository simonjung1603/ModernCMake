#include "MidiMessage.h"

const std::unordered_map<unsigned char, mb::EVENT_TYPE> mb::MidiMessage::m_EventTypeLUT = {
{static_cast<unsigned char>(0x8), EVENT_TYPE::NOTE_OFF},
{static_cast<unsigned char>(0x9), EVENT_TYPE::NOTE_ON},
{static_cast<unsigned char>(0xa), EVENT_TYPE::NOTE_AFTERTOUCH},
{static_cast<unsigned char>(0xb), EVENT_TYPE::CONTROLLER},
{static_cast<unsigned char>(0xc), EVENT_TYPE::PROGRAM_CHANGE},
{static_cast<unsigned char>(0xd), EVENT_TYPE::CHANNEL_AFTERTOUCH},
{static_cast<unsigned char>(0xe), EVENT_TYPE::PITCH_BEND}
};


mb::MidiMessage::MidiMessage(double timeStamp, std::vector<unsigned char> data)
{
    m_TimeStamp = timeStamp;
    if (data.size() < 2 || data.size() > 3)
    {
        throw std::runtime_error("The data parameter was of unexpected length");
    }
    unsigned char eventTypeNibble = data[0] >> 4;
    unsigned char channelNibble = data[0] - eventTypeNibble;
    unsigned char firstDataByte = data[1];
    unsigned char secondDataByte = data.size() == 3 ? data[2] : 0;

    m_EventType = m_EventTypeLUT.find(eventTypeNibble) == m_EventTypeLUT.end() ? EVENT_TYPE::UNINITIALIZED : m_EventTypeLUT.at(eventTypeNibble);
    m_Channel = channelNibble;
    m_FirstDataByte = firstDataByte;
    m_SecondDataByte = secondDataByte;
}

mb::MidiMessage::MidiMessage(double timeStamp, unsigned char eventType, unsigned char channel,
    unsigned char firstDataByte, unsigned char secondDataByte) : MidiMessage(timeStamp, m_EventTypeLUT.find(eventType) == m_EventTypeLUT.end() ? EVENT_TYPE::UNINITIALIZED : m_EventTypeLUT.at(eventType), channel, firstDataByte, secondDataByte)
{
}

mb::MidiMessage::MidiMessage(double timeStamp, EVENT_TYPE eventType, unsigned char channel, unsigned char firstDataByte,
    unsigned char secondDataByte) : m_TimeStamp(timeStamp), m_EventType(eventType), m_Channel(channel), m_FirstDataByte(firstDataByte), m_SecondDataByte(secondDataByte)
{
}

double mb::MidiMessage::GetTimeStamp() const
{
    return m_TimeStamp;
}

mb::EVENT_TYPE mb::MidiMessage::GetType() const
{
    return m_EventType;
}

unsigned char mb::MidiMessage::GetChannel() const
{
    return m_Channel;
}

unsigned char mb::MidiMessage::GetFirstDataByte() const
{
    return m_FirstDataByte;
}

unsigned char mb::MidiMessage::GetSecondDataByte() const
{
    return m_SecondDataByte;
}

mb::MidiMessage::operator bool() const
{
    if (this->GetType() == mb::EVENT_TYPE::UNINITIALIZED) return false;
    if (this->GetChannel() > 0xF) return false;
    return true;
}

