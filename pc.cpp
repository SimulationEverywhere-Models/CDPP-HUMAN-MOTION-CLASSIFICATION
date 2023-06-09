/*******************************************************************
*
*  DESCRIPTION: Atomic Model PC
*
*  AUTHOR: Seyed Ali Etemad
*
*  EMAIL: mailto://etemad@sce.carleton.ca
*
*  DATE: 4/11/2009
*
*******************************************************************/

/** include files **/
#include "pc.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Preprocessor
********************************************************************/
Pc::Pc( const string &name )
: Atomic( name )
, tr_ts( addInputPort( "tr_ts" ) )
, pcI( addInputPort( "pcI" ) )
, cam_pc( addInputPort( "cam_pc" ) )
, DOut( addOutputPort( "DOut" ) )
, pc_cam( addOutputPort( "pc_cam" ) )
, preparationTime( 0, 0, 0, 10 )
, waitTime( 0, 0, 10, 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;
	string time1( MainSimulator::Instance().getParameter( description(), "wait" ) ) ;

	if( time != "" )
		preparationTime = time ;
	if( time1 != "" )
		waitTime = time1 ;
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Pc::initFunction()
{
	state = Off;
	counter = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
********************************************************************/
Model &Pc::externalFunction( const ExternalMessage &msg )
{

		if( state == Off && msg.port() == pcI && msg.value() == 1)
			{
			state = Start_Cam_Train;
			holdIn( active, waitTime );
			}
		else if( ( state == Recv_Cam_Train || state == Start_Cam_Train) && msg.port() == tr_ts )
			{
			state = Off;
			passivate();
			}
		else if( state == Recv_Cam_Train && msg.port() == cam_pc )
			{
			state = Send_Cam_Train;
			holdIn( active, preparationTime );
			}
		else if( state == Off && msg.port() == pcI && msg.value() == 2)
			{
			state = Start_Cam_Test;
			holdIn( active, preparationTime );//wait
			}
		else if( state == Recv_Cam_Test && msg.port() == cam_pc )
			{
			state = Send_Cam_Test;
			holdIn( active, preparationTime );
			}


	return *this;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Pc::internalFunction( const InternalMessage & )
{
	switch (state){
				case Start_Cam_Train:
					state = Recv_Cam_Train ;
					passivate();
					break;

				case Send_Cam_Train:
					state = Start_Cam_Train ;
					holdIn( active, waitTime );
					break;

				case Start_Cam_Test:
					state = Recv_Cam_Test ;
					passivate();
					break;

				case Send_Cam_Test:
					state = Off ;
					passivate();
					break;
		};

	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Pc::outputFunction( const InternalMessage &msg )
{

	switch (state){
				case Start_Cam_Train:
					sendOutput( msg.time(), pc_cam, 1) ;
					break;

				case Send_Cam_Train:
					sendOutput( msg.time(), DOut, 1 )  ;
					break;

				case Start_Cam_Test:
					sendOutput( msg.time(), pc_cam, 1) ;
					break;

				case Send_Cam_Test:
					sendOutput( msg.time(), DOut, 1 )  ;
					break;
		};


	return *this ;
}
