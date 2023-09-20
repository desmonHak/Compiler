#ifndef __CLASS_H__
#define __CLASS_H__

#define class_c struct

#define ConstructorClass(NameClass) constructor_##NameClass
#define NewObjet(NameClass, NameObject) NameClass NameObject = { .exec = ConstructorClass(NameClass)}
#define CreateMethod(TypeRet, NameMethod, ...) TypeRet (*NameMethod)(__VA_ARGS__)
#define CreateAtribute(TypeData, NameAtribute) TypeData NameAtribute
#define MethodInvalid 0
#define IsValidMethod(MiMethod) MiMethod != MethodInvalid

#endif