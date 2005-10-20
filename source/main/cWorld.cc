/*
 *  cWorld.cc
 *  Avida2
 *
 *  Created by David on 10/18/05.
 *  Copyright 2005 Michigan State University. All rights reserved.
 *
 */

#include "cWorld.h"

#include "avida.h"
#include "cAvidaTriggers.h"
#include "cEnvironment.h"
#include "cEventManager.h"
#include "cHardwareManager.h"
#include "cPopulation.h"
#include "cTestCPU.h"
#include "cEventList.h"
#include "cInitFile.h"
#include "cTools.h"

cWorld::~cWorld()
{ 
  delete m_conf;
  delete m_pop;
  delete m_hw_mgr;
}

void cWorld::Setup() {
  // Setup Random Number Generator
  const int rand_seed = m_conf->RANDOM_SEED.Get();
  /* DDD - for right now we need to still use g_random
  cout << "Random Seed: " << rand_seed;
  m_rng.ResetSeed(rand_seed);
  if (rand_seed != m_rng.GetSeed()) cout << " -> " << m_rng.GetSeed();
  */
  cout << "Random Seed: " << rand_seed;
  g_random.ResetSeed(rand_seed);
  if (rand_seed != g_random.GetSeed()) cout << " -> " << g_random.GetSeed();
  cout << endl;
  
  // The default directory should end in a '/'.
  cString default_dir = m_conf->DEFAULT_DIR.Get();
  char dir_tail = default_dir[default_dir.GetSize() - 1];
  if (dir_tail != '\\' && dir_tail != '/') {
    default_dir += "/";
    m_conf->DEFAULT_DIR.Set(default_dir);
  }
  
  m_env = new cEnvironment(this);
  m_hw_mgr = new cHardwareManager(this);
  
  // Initialize the default environment...
  if (m_env->Load(m_conf->ENVIRONMENT_FILE.Get()) == false) {
    cerr << "Unable to load environment... aborting!" << endl;
    ExitAvida(-1);
  }
    
  // Setup the test CPUs.
  int rSize = m_env->GetResourceLib().GetSize();
  cTestCPU::Setup(this, rSize);

  m_pop = new cPopulation(this);

  //Setup Event List
  m_event_mgr = new cEventManager(this);
  m_event_list = new cEventList(m_event_mgr, new cAvidaTriggers(m_pop->GetStats()) );
  
  ReadEventListFile(m_conf->EVENT_FILE.Get());
  
  // Make sure the directory 'genebank' exits!
  cTools::MkDir("genebank", true);
}

void cWorld::ReadEventListFile(const cString & filename)
{
  cInitFile event_file(filename);
  
  // Load in the proper event list and set it up.
  event_file.Load();
  event_file.Compress();
  
  // Loop through the line_list and change the lines to events.
  for (int line_id = 0; line_id < event_file.GetNumLines(); line_id++) {
    m_event_list->AddEventFileFormat(event_file.GetLine(line_id));
  }
  
  ////////// Adding events from the Genesis file //////////
  // Max Updates and/or Max Generations
  if(m_conf->END_CONDITION_MODE.Get() == 0 ){
    if(m_conf->MAX_UPDATES.Get() >= 0 ){
      m_event_list->AddEvent( cEventTriggers::UPDATE, m_conf->MAX_UPDATES.Get(),
                            cEventTriggers::TRIGGER_ONCE,
                            cEventTriggers::TRIGGER_END, "exit", "");
    }
    if(m_conf->MAX_GENERATIONS.Get() >= 0 ){
      m_event_list->AddEvent( cEventTriggers::GENERATION,
                            m_conf->MAX_GENERATIONS.Get(),
                            cEventTriggers::TRIGGER_ONCE,
                            cEventTriggers::TRIGGER_END, "exit", "");
    }
  }else{
    if(m_conf->MAX_UPDATES.Get() >= 0 && m_conf->MAX_GENERATIONS.Get() >= 0 ){
      cString max_gen_str;
      max_gen_str.Set("%d", m_conf->MAX_GENERATIONS.Get());
      cString max_update_str;
      max_update_str.Set("%d", m_conf->MAX_UPDATES.Get());
      m_event_list->AddEvent( cEventTriggers::UPDATE, m_conf->MAX_UPDATES.Get(),
                            1, cEventTriggers::TRIGGER_END,
                            "exit_if_generation_greater_than", max_gen_str);
      m_event_list->AddEvent( cEventTriggers::GENERATION,
                            m_conf->MAX_GENERATIONS.Get(),
                            .01, cEventTriggers::TRIGGER_END,
                            "exit_if_update_greater_than", max_update_str);
    }
  }
}

void cWorld::GetEvents()
{  
  if (m_pop->GetSyncEvents() == true) {
    SyncEventList();
    m_pop->SetSyncEvents(false);
  }
  m_event_list->Process();
}

int cWorld::GetNumInstructions()
{
  return m_hw_mgr->GetInstSet().GetSize();
}

int cWorld::GetNumTasks()
{
  return m_env->GetTaskLib().GetSize(); 
}

int cWorld::GetNumReactions()
{
  return m_env->GetReactionLib().GetSize();
}

int cWorld::GetNumResources()
{
  return m_env->GetResourceLib().GetSize();
}
