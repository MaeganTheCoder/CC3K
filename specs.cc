#include "specs.h"
#include "potion.h"
#include <sstream>
using namespace std;

Specs::Specs(int atk, int def, int hp, string raceName):
 atk{atk}, def{def}, hp{hp}, maxHp{hp}, atkBoost{0}, defBoost{0}, gold{0}, raceName{raceName} {

}

Specs::~Specs() {

}

int Specs::getAtk() {
  return atk + atkBoost;
}

int Specs::getDef() {
  return def + defBoost;
}

int Specs::getHp() {
  return hp;
}

double Specs::getGold() {
  return gold;
}

void Specs::setHp(int newHp) {
  // hp cannot go higher than maxHp
  hp = newHp <= maxHp ? newHp : maxHp;
}

void Specs::addGold(int amount) {
  gold += amount;
}

void Specs::setAttackBoost(int boost) {
  atkBoost += boost;
}

void Specs::setDefenceBoost(int boost) {
  defBoost += boost;
}

void Specs::setHpThroughPotion(int newHp) {
  if (newHp <0) newHp=0;
  setHp(newHp);
}

void Specs::reset() {
  atkBoost = 0;
  defBoost = 0;
}

double Specs::calculateScore() {
  return gold;
}

string Specs::getRaceName() {
  return raceName;
}

HumanSpecs::HumanSpecs(): Specs(20, 20, 140, "Human") {

}

double HumanSpecs::calculateScore() {
  return gold * 2;
}

DwarfSpecs::DwarfSpecs(): Specs(20, 30, 100, "Dwarf") {

}

void DwarfSpecs::addGold(int amount) {
  gold += (2 * amount);
}

ElfSpecs::ElfSpecs(): Specs(30, 10, 140, "Elf") {

}

void ElfSpecs::setAttackBoost(int boost) {
  atkBoost = boost >= 0 ? atkBoost + boost : atkBoost - boost;
}

void ElfSpecs::setDefenceBoost(int boost) {
  defBoost = boost >= 0 ? defBoost + boost : defBoost - boost;
}

void ElfSpecs::setHpThroughPotion(int newHp) {
  // elfs cannot get hurt through a potion.
  newHp = newHp >= hp ? newHp : (hp - newHp) + hp;
  if (newHp<0) newHp=0;
  setHp(newHp);
}

OrcSpecs::OrcSpecs(): Specs(30, 25, 180, "Orc") {

}

void OrcSpecs::addGold(int amount) {
  LOG("Orc picked up a " << amount << " sized treasure");
  LOG("gold was: " << gold);
  gold += (amount / 2.0);
  LOG("is now: " << gold);
}
