////////////////////////////////////////////////////////
//
// gem_projectM
// Milkdrop compatible music visualizer for Pure Data
//
// Copyright (c) Damian Christey 
// damian.christey@gmail.com
// 
// Based on example code from scopeXYZ~.cpp in GEM 
// Copyright (c) zmoelnig@iem.kug.ac.at
// GEM - Graphics Environment for Multimedia
//
// projectM -- Milkdrop-esque visualisation SDK
// Copyright (C)2003-2007 projectM Team
//
// Implementation file
//
/////////////////////////////////////////////////////////

#define HELPSYMBOL "gem_projectM"

#include "gem_projectM.h"

#include<iostream>
using namespace std;

CPPEXTERN_NEW(gem_projectM);

/////////////////////////////////////////////////////////
//
// gem_projectM
//
/////////////////////////////////////////////////////////
// Constructor
//
/////////////////////////////////////////////////////////
gem_projectM :: gem_projectM() 
{
  m_projectM = 0;

  // create the new signal inlet
  m_inAudio = inlet_new(this->x_obj, &this->x_obj->ob_pd, &s_signal, &s_signal);

  // create an outlet to send texture ID
  m_outTexID = outlet_new(this->x_obj, &s_float);

}

/////////////////////////////////////////////////////////
// Destructor
//
/////////////////////////////////////////////////////////
gem_projectM :: ~gem_projectM()
{
  if(m_outTexID) outlet_free(m_outTexID);
  m_outTexID=NULL;

  if(m_inAudio) inlet_free(m_inAudio);
  m_inAudio=NULL;

  destroyProjectM();
}

/////////////////////////////////////////////////////////
// render
//
/////////////////////////////////////////////////////////
void gem_projectM :: render(GemState *)
{
  if (m_projectM) {
    m_projectM->renderFrame();
  }
}

/////////////////////////////////////////////////////////
// postrender
//
/////////////////////////////////////////////////////////
void gem_projectM :: postrender(GemState *)
{
    
}

////////////////////////////////////////////////////////
// startRendering
//
////////////////////////////////////////////////////////
void gem_projectM :: startRendering()
{
  if (m_projectM == 0) {
    cout << "Starting...\n";
    m_projectM = new projectM ("config.inp");
    cout << "Created projectM object.\n";
    setup_GL();
    textureID = m_projectM->initRenderToTexture();
    cout << "Got texture ID: " << textureID << "\n";
    outlet_float(m_outTexID, textureID);
  }
    
  // For some reason, rendering doesn't start until you set the title
  m_projectM->projectM_setTitle(" ");
}

////////////////////////////////////////////////////////
// stopRendering
//
/////////////////////////////////////////////////////////
void gem_projectM :: stopRendering()
{
  destroyProjectM();
}

/////////////////////////////////////////////////////////
// set title to message string
//
/////////////////////////////////////////////////////////
void gem_projectM :: titleMess(std::string new_title)
{
  if(new_title.empty())return;
  m_projectM->projectM_setTitle(new_title);
}


/////////////////////////////////////////////////////////
// switch to next preset
//
/////////////////////////////////////////////////////////
void gem_projectM :: nextPresetMess()
{
  if (m_projectM) {
    m_projectM->selectNext(false);
  }
}

/////////////////////////////////////////////////////////
// switch to previous preset
//
/////////////////////////////////////////////////////////
void gem_projectM :: previousPresetMess()
{
  if (m_projectM) {
    m_projectM->selectPrevious(false);
  }
}

/////////////////////////////////////////////////////////
// switch to random preset
//
/////////////////////////////////////////////////////////
void gem_projectM :: randomPresetMess()
{
  if (m_projectM) {
    m_projectM->selectRandom(false);
  }
}


/////////////////////////////////////////////////////////
// static member function
//
/////////////////////////////////////////////////////////
void gem_projectM :: obj_setupCallback(t_class *classPtr)
{
  class_addcreator(reinterpret_cast<t_newmethod>(create_gem_projectM),
                   gensym("gem_projectM"), A_DEFFLOAT, A_NULL);
  class_addmethod(classPtr, reinterpret_cast<t_method>(&gem_projectM::dspCallback),
                  gensym("dsp"), A_NULL);
  class_addmethod(classPtr, nullfn, gensym("signal"), A_NULL);

  CPPEXTERN_MSG1(classPtr, "title", titleMess, std::string);
  CPPEXTERN_MSG0(classPtr, "next", nextPresetMess);
  CPPEXTERN_MSG0(classPtr, "previous", previousPresetMess);
  CPPEXTERN_MSG0(classPtr, "random", randomPresetMess);
  
}
	
void gem_projectM :: destroyProjectM()
{
  if ( m_projectM ) {
    delete ( m_projectM );
    m_projectM = 0;
  }
} 

void gem_projectM :: setup_GL()
{
  /* TODO: Fix fullscreen issues */
}

void gem_projectM ::  dspCallback(void *data, t_signal** sp)
{
  dsp_add(perform, 3, data, sp[1]->s_vec, sp[1]->s_n);
}

void gem_projectM :: perform(unsigned int count, t_sample* audioIn)
{
  if (m_projectM) {
    m_projectM->pcm()->addPCMfloat(audioIn, count);
  }
}

t_int* gem_projectM :: perform(t_int* w)
{
  int index=1;
  gem_projectM *x = GetMyClass(reinterpret_cast<void*>(w[index++]));
  t_sample* audioIn = reinterpret_cast<t_sample*>(w[index++]);
  t_int n = (w[index++]);

  x->perform(n, audioIn);

  return (w+index);
}
