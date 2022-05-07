/**
 * @file save-class-diagram.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#include "../src/ClassDiagram.h"
#include "../src/Generalization.h"
#include "../src/FileClassDiagramRepository.h"
#include "../src/FileSequenceDiagramRepository.h"

/**
 * Simple test for saving class diagram
 */
int main()
{
    // Class classDiagram
    ClassDiagram classDiagram{};

    Class electronicDevice{"ElectronicDevice", std::tuple<int, int>{10, 10}};
    electronicDevice.addAttribute(ClassAttribute{"price", AccessModifier::PROTECTED, "int"});
    electronicDevice.addAttribute(ClassAttribute{"color", AccessModifier::PROTECTED, "string"});
    classDiagram.addClass(electronicDevice);

    Class phone{"Phone", std::tuple<int, int>{410, 10}};
    phone.addAttribute(ClassAttribute{"batterySize", AccessModifier::PRIVATE, "int"});
    phone.addMethod(ClassMethod{"isValuable", AccessModifier::PUBLIC, std::vector<MethodParameter> {}, "bool"});
    phone.addMethod(ClassMethod{"setColor", AccessModifier::PUBLIC, std::vector<MethodParameter> {
            MethodParameter{"newColor", "string"}
    }});
    classDiagram.addClass(phone);

    Generalization phoneInheritsElectronicDevice{&phone, &electronicDevice};
    classDiagram.addRelationship(&phoneInheritsElectronicDevice);

    // Sequence classDiagram
    SequenceDiagram sequenceDiagram{};

    Actor user{"User"};
    sequenceDiagram.addActor(user);

    Object samsungPhone{&phone, 0.3, 0.7, "someSamsung"};
    sequenceDiagram.addObject(samsungPhone);

    Object xiaomiPhone{&phone, 0.2, 0.3, "someXiaomi"};
    sequenceDiagram.addObject(xiaomiPhone);

    Message createSamsung{"<<create>>", MessageType::CREATE, &user, &samsungPhone, 0.2};
    sequenceDiagram.addMessage(createSamsung);
    Message createXiaomi{"<<create>>", MessageType::CREATE, &user, &xiaomiPhone, 0.1};
    sequenceDiagram.addMessage(createXiaomi);
    Message isSamsungValuable{"isValuable()", MessageType::SYNC, &user, &samsungPhone, 0.4};
    sequenceDiagram.addMessage(isSamsungValuable);
    Message samsungValuableReply{"result", MessageType::REPLY, &samsungPhone, &user, 0.6};
    Message destroyXiaomi{"<<destroy>>", MessageType::DESTROY, &user, &xiaomiPhone, 0.4};
    sequenceDiagram.addMessage(destroyXiaomi);

    FileSequenceDiagramRepository repo{classDiagram, "examples/sequence-diagram-output.xml"};
    repo.saveDiagram(sequenceDiagram);

    return 0;
}