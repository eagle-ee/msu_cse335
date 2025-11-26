/**
 * @file JoeFactory.cpp
 * @author b3big
 */

#include "pch.h"
#include "JoeFactory.h"
#include "ImageDrawable.h"
#include "PolyDrawable.h"
#include "HeadTop.h"

using namespace std;

/**
 * This is a factory method that creates our Joe actor.
 * @param imagesDir Directory that contains the images for this application
 * @return Pointer to an actor object.
 */
std::shared_ptr<Actor> JoeFactory::Create(std::wstring imagesDir)
{
    shared_ptr<Actor> actor = make_shared<Actor>(L"JoeMama");

    auto coat = make_shared<ImageDrawable>(L"Coat", imagesDir + L"/joeMama_coat.png");
    coat->SetCenter(wxPoint(44, 138));
    coat->SetPosition(wxPoint(0, -114));
    actor->SetRoot(coat);

    auto lleg = make_shared<ImageDrawable>(L"Left Leg", imagesDir + L"/joeMama_lleg.png");
    lleg->SetCenter(wxPoint(11, 9));
    lleg->SetPosition(wxPoint(17, 0));
    coat->AddChild(lleg);

    auto rleg = make_shared<ImageDrawable>(L"Right Leg", imagesDir + L"/joeMama_rleg.png");
    rleg->SetCenter(wxPoint(39, 9));
    rleg->SetPosition(wxPoint(-27, 0));
    coat->AddChild(rleg);

    auto headb = make_shared<ImageDrawable>(L"Head Bottom", imagesDir + L"/joeMama_headb.png");
    headb->SetCenter(wxPoint(44, 31));
    headb->SetPosition(wxPoint(0, -130));
    coat->AddChild(headb);

    auto headt = make_shared<HeadTop>(L"Head Top", imagesDir + L"/joeMama_headt.png");
    headt->SetCenter(wxPoint(55, 109));
    headt->SetEyesCenter(wxPoint(50, 60));
    headt->SetPosition(wxPoint(6, -15));
    headb->AddChild(headt);

    auto larm = make_shared<PolyDrawable>(L"Left Arm");
    larm->SetColor(wxColour(20, 20, 20));
    larm->SetPosition(wxPoint(50, -130));
    larm->AddPoint(wxPoint(-7, -7));
    larm->AddPoint(wxPoint(-7, 96));
    larm->AddPoint(wxPoint(8, 96));
    larm->AddPoint(wxPoint(8, -7));
    coat->AddChild(larm);

    auto rarm = make_shared<PolyDrawable>(L"Right Arm");
    rarm->SetColor(wxColour(20, 20, 20));
    rarm->SetPosition(wxPoint(-45, -130));
    rarm->AddPoint(wxPoint(-7, -7));
    rarm->AddPoint(wxPoint(-7, 96));
    rarm->AddPoint(wxPoint(8, 96));
    rarm->AddPoint(wxPoint(8, -7));
    coat->AddChild(rarm);

    auto lhand = make_shared<PolyDrawable>(L"Left Hand");
    lhand->SetColor(wxColour(233, 158, 160));
    lhand->SetPosition(wxPoint(0, 96));
    lhand->AddPoint(wxPoint(-12, -2));
    lhand->AddPoint(wxPoint(-12, 17));
    lhand->AddPoint(wxPoint(11, 17));
    lhand->AddPoint(wxPoint(11, -2));
    larm->AddChild(lhand);

    auto rhand = make_shared<PolyDrawable>(L"Right Hand");
    rhand->SetColor(wxColour(233, 158, 160));
    rhand->SetPosition(wxPoint(0, 96));
    rhand->AddPoint(wxPoint(-12, -2));
    rhand->AddPoint(wxPoint(-12, 17));
    rhand->AddPoint(wxPoint(11, 17));
    rhand->AddPoint(wxPoint(11, -2));
    rarm->AddChild(rhand);


    actor->AddDrawable(larm);
    actor->AddDrawable(rarm);
    actor->AddDrawable(rhand);
    actor->AddDrawable(lhand);
    actor->AddDrawable(rleg);
    actor->AddDrawable(lleg);
    actor->AddDrawable(coat);
    actor->AddDrawable(headb);
    actor->AddDrawable(headt);

    return actor;
}