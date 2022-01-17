#include "ConfineGeneratorMessenger.hh"
#include "ConfineGenerator.hh"

#include <G4SystemOfUnits.hh>

ConfineGeneratorMessenger::ConfineGeneratorMessenger(ConfineGenerator *gen)
    : myGen{gen}, cgsDir{new G4UIdirectory("/cgs/")},
      shapeCmd{new G4UIcmdWithAString("/cgs/shape", this)},
      confineCmd{new G4UIcmdWithAString("/cgs/confine", this)},
      confineDir{new G4UIdirectory("/cgs/conf")}, confineMaterialCmd{
          new G4UIcmdWithAString("/cgs/conf/material", this)},
      particleCmd{new G4UIcmdWithAString("/cgs/particle", this)},
      ionCmd{new G4UIcommand("/cgs/ion", this)},
      centerCmd{new G4UIcmdWith3VectorAndUnit("/cgs/centre", this)},
      radiusCmd{new G4UIcmdWithADoubleAndUnit("/cgs/radius", this)},
      halfXCmd{new G4UIcmdWithADoubleAndUnit("/cgs/halfx", this)},
      halfYCmd{new G4UIcmdWithADoubleAndUnit("/cgs/halfy", this)},
      halfZCmd{new G4UIcmdWithADoubleAndUnit("/cgs/halfz", this)},
      energyCmd{new G4UIcmdWithADoubleAndUnit("/cgs/energy", this)} {
    cgsDir->SetGuidance("confined particle source control commands.");

    shapeCmd->SetGuidance("Set shape of particle source.");
    shapeCmd->SetGuidance("Available shapes: Point Cylinder, Box");
    shapeCmd->SetParameterName("shape", true);
    shapeCmd->SetDefaultValue("Point");
    shapeCmd->SetCandidates("Point Cylinder Box");

    confineCmd->SetGuidance("Set confined detector of particle");
    confineCmd->SetParameterName("confine", false);

    confineDir->SetGuidance("Confine command sub directory");
    confineMaterialCmd->SetGuidance("Set confined material of particle");
    confineMaterialCmd->SetParameterName("confineMaterial", false);

    particleCmd->SetGuidance("Set particle type");
    particleCmd->SetParameterName("particle", false);
    particleCmd->SetDefaultValue("gamma");

    ionCmd->SetGuidance("Set the ion properties when the particle type is ion");
    ionCmd->SetGuidance("[usage] /gps/ion Z A");
    ionCmd->SetGuidance("        Z:(int) AtomicNumber");
    ionCmd->SetGuidance("        A:(int) AtomicMass");

    G4UIparameter* param;
    param = new G4UIparameter("Z",'i',false);
    param->SetDefaultValue("92");
    ionCmd->SetParameter(param);
    param = new G4UIparameter("A",'i',false);
    param->SetDefaultValue("238");
    ionCmd->SetParameter(param);

    centerCmd->SetGuidance("Set center of the source");
    centerCmd->SetParameterName("x", "y", "z", true, true);
    centerCmd->SetDefaultUnit("cm");
    centerCmd->SetDefaultValue(G4ThreeVector(0, 0, 0));

    radiusCmd->SetGuidance("Set radius of the cylinder shape source");
    radiusCmd->SetParameterName("radius", false);
    radiusCmd->SetDefaultUnit("cm");

    halfXCmd->SetGuidance("Set x half length of source.");
    halfXCmd->SetParameterName("Halfx",false,false);
    halfXCmd->SetDefaultUnit("cm");

    halfYCmd->SetGuidance("Set y half length of source.");
    halfYCmd->SetParameterName("Halfy",false,false);
    halfYCmd->SetDefaultUnit("cm");

    halfZCmd->SetGuidance("Set z half length of source.");
    halfZCmd->SetParameterName("Halfz",false,false);
    halfZCmd->SetDefaultUnit("cm");

    energyCmd->SetGuidance("Set kinetic energy.");
    energyCmd->SetParameterName("Energy",false,false);
    energyCmd->SetDefaultUnit("keV");
}

void ConfineGeneratorMessenger::SetNewValue(G4UIcommand *command,
                                            G4String newValues) {
    if (command == shapeCmd.get()) {
        myGen->setShape(newValues);
    } else if (command == confineCmd.get()) {
        myGen->setConfineVolume(newValues);
    } else if (command == confineMaterialCmd.get()) {
	myGen->setConfineMaterial(newValues);
    } else if (command == particleCmd.get()) {
	myGen->setParticle(newValues);
    } else if (command == centerCmd.get()) {
        myGen->setCenter(centerCmd->GetNew3VectorValue(newValues));
    } else if (command == radiusCmd.get()) {
        myGen->setRadius(radiusCmd->GetNewDoubleValue(newValues));
    } else if (command == halfXCmd.get()) {
        myGen->setHalfX(halfXCmd->GetNewDoubleValue(newValues));
    } else if (command == halfYCmd.get()) {
        myGen->setHalfY(halfYCmd->GetNewDoubleValue(newValues));
    } else if (command == halfZCmd.get()) {
        myGen->setHalfZ(halfZCmd->GetNewDoubleValue(newValues));
    } else if (command == energyCmd.get()) {
        myGen->setEnergy(energyCmd->GetNewDoubleValue(newValues));
    } else {
        G4cout << "Wrong command" << G4endl;
    }
}