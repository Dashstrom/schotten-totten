/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "mainwindow.hpp"

#include <QDebug>
#include <QPixmapCache>

#include "game_model.hpp"
#include "game_view.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  // We need a big boy cache
  QPixmapCache::setCacheLimit(500000000);
  // Since this is a QMainWindow we cannot set a layout,
  // we can only set a central widget.
  GameModel* gameModel = new GameModel();
  GameView* gameView = new GameView(gameModel, this);
  QIcon icon("resources/favicon.ico");

  this->setWindowTitle("Schotten Totten");
  this->setCentralWidget(gameView);
  this->setMinimumHeight(600);
  this->setMinimumWidth(600);
  this->setWindowIcon(icon);
}
