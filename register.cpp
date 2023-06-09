/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Seyed Ali Etemad
*
*  EMAIL: mailto://etemad@sce.carleton.ca
*
*  DATE: 4/11/2009
*
*******************************************************************/

#include "modeladm.h"
#include "mainsimu.h"
#include "pc.h"        // class Pc
#include "cameras.h"        // class Cameras
#include "preprocessor.h"        // class Preprocessor
#include "classifier.h"        // class Classifier

void MainSimulator::registerNewAtomics()
{

	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Pc>(), "Pc" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Cameras>(), "Cameras" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Preprocessor>(), "Preprocessor" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Classifier>(), "Classifier" ) ;  }

