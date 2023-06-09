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

/** include files **/
#include "cameras.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Cameras
********************************************************************/
Cameras::Cameras( const string &name )
: Atomic( name )
, pc_cam( addInputPort( "pc_cam" ) )
, cam_pc( addOutputPort( "cam_pc" ) )
, preparationTime( 0, 0, 6, 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Cameras::initFunction()
{
	this-> passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
********************************************************************/
Model &Cameras::externalFunction( const ExternalMessage &msg )
{
	if (this->state() == passive)
		{
			holdIn( active, preparationTime );
		}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Cameras::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Cameras::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), cam_pc, 1) ;
	return *this ;
}
