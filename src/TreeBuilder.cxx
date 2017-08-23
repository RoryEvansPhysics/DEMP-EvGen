#include "TreeBuilder.hxx"
#include "Particle.hxx"

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

TreeBuilder::TreeBuilder(char * name)
{
  tree_name = name;
  file_name = "Output.root";

  File_Out = new TFile(file_name, "RECREATE");
  Tree_Out = new TTree(tree_name, tree_name);


  Tree_Out->SetAutoSave();

  nParticles = 0;
}

void TreeBuilder::AddParticle(Particle * p)
{
  ParticleList.push_back(p);
  vector< double* >* TempVec = new vector<double*>(5);
  // Vector elements must be initialized to non-null
  // pointers
  for (int i = 0; i<5; i++)
    TempVec->at(i) = new double();

  PropList.push_back(TempVec);

  char * p_name = p->GetName();
  char b_name[100]; // Branch name
  char l_list[100]; // Leaf list

  strcpy(b_name, p_name);
  strcat(b_name, "_pid");
  strcpy(l_list, b_name);
  strcat(l_list, "/D");
  Tree_Out->Branch(b_name,TempVec->at(0),l_list);

  strcpy(b_name, p_name);
  strcat(b_name, "_Px");
  strcpy(l_list, b_name);
  strcat(l_list, "/D");
  Tree_Out->Branch(b_name,TempVec->at(1),l_list);

  strcpy(b_name, p_name);
  strcat(b_name, "_Py");
  strcpy(l_list, b_name);
  strcat(l_list, "/D");
  Tree_Out->Branch(b_name,TempVec->at(2),l_list);

  strcpy(b_name, p_name);
  strcat(b_name, "_Pz");
  strcpy(l_list, b_name);
  strcat(l_list, "/D");
  Tree_Out->Branch(b_name,TempVec->at(3),l_list);


  strcpy(b_name, p_name);
  strcat(b_name, "_E");
  strcpy(l_list, b_name);
  strcat(l_list, "/D");
  Tree_Out->Branch(b_name,TempVec->at(4),l_list);

  nParticles++;

  //cout << ParticleList[0] << endl;
  //cout << TempVec->at(1) << endl;
  //cout << PropList.at(0)->at(1) << endl;
}

void TreeBuilder::Fill()
{
  Retrieve();
  Tree_Out->Fill();
}

// Particles have private data members that must be retrieved
// to be copied to an accessible address to be added to the
// TTree.
void TreeBuilder::Retrieve()
{
  for (int i = 0; i < nParticles; i++){
    //cout << PropList.at(i)->at(1) <<endl;
    *PropList.at(i)->at(0) = (double)ParticleList.at(i)->GetPid();
    *PropList.at(i)->at(1) = ParticleList.at(i)->Px();
    *PropList.at(i)->at(2) = ParticleList.at(i)->Py();
    *PropList.at(i)->at(3) = ParticleList.at(i)->Pz();
    *PropList.at(i)->at(4) = ParticleList.at(i)->E();
    //cout <<  &PropList.at(i)->at(1) << endl;
  }
}

void TreeBuilder::Save()
{
  Tree_Out->AutoSave();
  //File_Out->Write();
}
