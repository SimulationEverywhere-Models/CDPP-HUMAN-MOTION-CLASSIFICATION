/*******************************************************************
*
*  DESCRIPTION: Atomic Model pc
*
*  AUTHOR: Seyed Ali Etemad
*
*  EMAIL: mailto://etemad@sce.carleton.ca
*
*  DATE: 4/11/2009
*
*******************************************************************/

#ifndef __PC_H
#define __PC_H

//#include <list>
#include "atomic.h"     // class Atomic

class Pc : public Atomic
{
public:
	Pc( const string &name = "Pc" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &pcI;
	const Port &tr_ts;
	const Port &cam_pc;
	Port &pc_cam;
	Port &DOut;
	Time preparationTime, waitTime;
	int counter;

		enum State{
			Off,
			Start_Cam_Test,
			Start_Cam_Train,
			Send_Cam_Train,
			Send_Cam_Test,
			Recv_Cam_Train,
			Recv_Cam_Test,
		};
		State state;

};	// class pc

// ** inline ** //
inline
string Pc::className() const
{
	return "Pc" ;
}

#endif   //__PC_H
