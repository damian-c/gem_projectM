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
/////////////////////////////////////////////////////////

#ifndef _INCLUDE__GEM_PIXES_gem_projectM_H_
#define _INCLUDE__GEM_PIXES_gem_projectM_H_

#include "Base/GemBase.h"

#include <libprojectM/projectM.hpp>

/*-----------------------------------------------------------------
-------------------------------------------------------------------
CLASS
    gem_projectM

    Loads Milkdrop presets and uses OpenGL to render them to a texture

KEYWORDS
    visualization

DESCRIPTION

    Inlet for control messages
    Outlet for texture ID

-----------------------------------------------------------------*/
class GEM_EXTERN gem_projectM : public GemBase
{
  CPPEXTERN_HEADER(gem_projectM, GemBase);

 public:

  //////////
  // Constructor
  gem_projectM();


 protected:

  //////////
  // Destructor
  virtual ~gem_projectM();

  // Inlets and Outlets
  t_outlet *m_outTexID;
  t_inlet *m_inAudio;

  //////////
  // Do the rendering
  virtual void render(GemState *state);

  //////////
  // 
  virtual void postrender(GemState *state);

  //////////
  // Establish texture object
  virtual void startRendering(void);

  //////////
  // Delete texture object
  virtual void stopRendering(void);

  // set title to message string
  void titleMess(std::string);

  // switch presets
  void nextPresetMess();
  void previousPresetMess();
  void randomPresetMess();

  void perform(unsigned int count, t_sample*X);

 private:
	
  // Output texture ID
  unsigned textureID;

  void setup_GL();

  void destroyProjectM();

  // projectM object
  projectM *m_projectM;

  static void dspCallback(void *data, t_signal** sp);
  static t_int* perform(t_int* w);

};

#endif	// for header file
