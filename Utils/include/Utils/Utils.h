#pragma once

#define GET_SET_FUN_DECLAR(type, member, name) \
protected:\
    type member;\
public:\
    type Get##name();\
    void Set##name(type val);

#define GET_SET_FUN_DEFINE(type, class, member, name) \
type class::Get##name()\
{\
    return member;\
}\
void class::Set##name(type val)\
{\
    member = val;\
}
