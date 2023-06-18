/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "stone_view.hpp"

#include <QDebug>
#include <QGridLayout>
#include <QWidget>

#include "button_view.hpp"
#include "formation_view.hpp"
#include "player_model.hpp"
#include "stone_model.hpp"

StoneView::StoneView(StoneModel& model, PlayerModel& player, PlayerModel& enemy,
                     size_t skin, QWidget* parent)
    : QWidget(parent), m_skin(skin), stone(model) {
  qDebug() << "Creating stone view";

  layout = new QGridLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);

  formationView1 = new FormationView(this);
  formationView1->setCards(stone.getCards(player));
  formationView2 = new FormationView(this);
  formationView2->setCards(stone.getCards(enemy));

  QString stonePath("resources/stones/" + QString::number(m_skin % 9) +
                    "_.jpg");
  QString emptyPath("resources/stones/empty.png");

  // compute responsive dimensions
  if (stone.isClaimed()) {
    stoneButton = new ButtonView(emptyPath, this);
    if (stone.isClaimedBy(player)) {
      stoneButtonTop = new ButtonView(emptyPath, this);
      stoneButtonBot = new ButtonView(stonePath, this);
    } else {
      stoneButtonTop = new ButtonView(stonePath, this);
      stoneButtonBot = new ButtonView(emptyPath, this);
    }
  } else {
    stoneButton = new ButtonView(stonePath, this);
    stoneButtonTop = new ButtonView(emptyPath, this);
    stoneButtonBot = new ButtonView(emptyPath, this);
  }

  layout->addWidget(stoneButtonTop, 0, 0);
  layout->addWidget(formationView2, 1, 0);
  layout->addWidget(stoneButton, 2, 0);
  layout->addWidget(formationView1, 3, 0);
  layout->addWidget(stoneButtonBot, 4, 0);

  // define the relative proportions of the rows
  layout->setRowStretch(0, 60);
  layout->setRowStretch(1, 100);
  layout->setRowStretch(2, 60);
  layout->setRowStretch(3, 100);
  layout->setRowStretch(4, 60);

  connect(&stone, &StoneModel::changed, this, [this, &player, &enemy] {
    this->formationView1->setCards(this->stone.getCards(player));
    this->formationView2->setCards(this->stone.getCards(enemy));
  });

  connect(formationView1, &FormationView::clicked, this,
          [&] { emit action(StoneView::Formation1); });
  connect(stoneButton, &ButtonView::clicked, this,
          [&] { emit action(StoneView::Stone); });
  connect(formationView2, &FormationView::clicked, this,
          [&] { emit action(StoneView::Formation2); });
}
