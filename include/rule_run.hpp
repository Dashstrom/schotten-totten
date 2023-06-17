/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#pragma once

#include <QList>
#include <algorithm>

#include "card_model.hpp"
#include "rule.hpp"

class RuleRun : public Rule {
 public:
  RuleRun() : Rule("run") {}
  bool match(QList<CardModel*> cards) const override {
    /* Check if cards have successive strength */
    QList<CardModel*> cardsCopy = cards;
    std::sort(cardsCopy.begin(), cardsCopy.end(),
              [](CardModel* card, CardModel* other) {
                return card->strength() < other->strength();
              });
    CardModel* previous = nullptr;
    for (auto card : cards) {
      if (previous != nullptr && card->strength() != previous->strength() + 1)
        return false;
    }
    return true;
  }
};
