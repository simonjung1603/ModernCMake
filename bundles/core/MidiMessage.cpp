#include "MidiMessage.h"

mb::EVENT_TYPE mb::MidiMessage::GetType() const
{
    return m_EventType;
}

unsigned char mb::MidiMessage::GetChannel() const
{
    return m_Channel;
}

unsigned char mb::MidiMessage::GetSecondByte() const
{
    return m_SecondByte;
}

unsigned char mb::MidiMessage::GetThirdByte() const
{
    return m_ThirdByte;
}

mb::MidiMessage::operator bool() const
{
    if (this->GetType() == mb::EVENT_TYPE::UNINITIALIZED) return false;
    if (this->GetChannel() > 0xF) return false;
    return true;
}
