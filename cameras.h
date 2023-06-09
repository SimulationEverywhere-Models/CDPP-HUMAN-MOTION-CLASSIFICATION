/*******************************************************************
*
*  DESCRIPTION: Atomic Model cameras
*
*  AUTHOR: Seyed Ali Etemad
*
*  EMAIL: mailto://etemad@sce.carleton.ca
*
*  DATE: 4/11/2009
*
*******************************************************************/

#ifndef __CAMERAS_H
#define __CAMERAS_H

//#include <list>
#include "atomic.h"     // class Atomic

class Cameras : public Atomic
{
public:
	Cameras( const string &name = "Cameras" );		//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &pc_cam;
	Port &cam_pc;
	Time preparationTime;


};	// class Preprocessor

// ** inline ** //
inline
string Cameras::className() const
{
	return "Cameras" ;
}

#endif   //__CAMERAS_H
