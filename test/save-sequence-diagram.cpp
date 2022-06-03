/**
 * @file save-class-diagram.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */

#include "../src/ClassDiagram.h"
#include "../src/Generalization.h"
#include "../src/FileSequenceDiagramRepository.h"

/**
 * Simple test for saving class diagram
 */
int main()
{
    // Class classDiagram
    ClassDiagram classDiagram{};

    auto electronicDevice = new Class{"ElectronicDevice", std::tuple<int, int>{10, 10}};
    electronicDevice->addAttribute(ClassAttribute{"price", AccessModifier::PROTECTED, "int"});
    electronicDevice->addAttribute(ClassAttribute{"color", AccessModifier::PROTECTED, "string"});
    classDiagram.addClass(electronicDevice);

    auto phone = new Class{"Phone", std::tuple<int, int>{410, 10}};
    phone->addAttribute(ClassAttribute{"batterySize", AccessModifier::PRIVATE, "int"});
    phone->addMethod(ClassMethod{"isValuable", AccessModifier::PUBLIC, std::vector<MethodParameter> {}, "bool"});
    phone->addMethod(ClassMethod{"setColor", AccessModifier::PUBLIC, std::vector<MethodParameter> {
            MethodParameter{"newColor", "string"}
    }});
    classDiagram.addClass(phone);

    auto phoneInheritsElectronicDevice = new Generalization{phone, electronicDevice};
    classDiagram.addRelationship(phoneInheritsElectronicDevice);

    // Sequence classDiagram
    SequenceDiagram sequenceDiagram{};

    auto user = new Actor {"User"};
    sequenceDiagram.addActor(user);

    auto samsungPhone = new Object{phone, 0.3, 0.7, "someSamsung"};
    sequenceDiagram.addObject(samsungPhone);

    auto xiaomiPhone = new Object{phone, 0.2, 0.3, "someXiaomi"};
    sequenceDiagram.addObject(xiaomiPhone);

    auto createSamsung = new Message{MethodReference{"<<create>>"}, MessageType::CREATE, user, samsungPhone, 0.2};
    sequenceDiagram.addMessage(createSamsung);
    auto createXiaomi = new Message{MethodReference{"<<create>>"}, MessageType::CREATE, user, xiaomiPhone, 0.1};
    sequenceDiagram.addMessage(createXiaomi);
    auto isSamsungValuable = new Message{MethodReference{"isValuable()"}, MessageType::SYNC, user, samsungPhone, 0.4};
    sequenceDiagram.addMessage(isSamsungValuable);
    auto samsungValuableReply = new Message{MethodReference{"result"}, MessageType::REPLY, samsungPhone, user, 0.6};
    auto destroyXiaomi = new Message{MethodReference{"<<destroy>>"}, MessageType::DESTROY, user, xiaomiPhone, 0.4};
    sequenceDiagram.addMessage(samsungValuableReply);
    sequenceDiagram.addMessage(destroyXiaomi);

    FileSequenceDiagramRepository repo{classDiagram, "examples/sequence-diagram-output.xml"};
    repo.saveDiagram(sequenceDiagram);

    return 0;
}