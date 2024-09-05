#include "Resolver.hpp"
#include "Animations.hpp"

void C_Resolver::HandleMiss( C_BasePlayer* Player, LagRecord_t* m_Record )
{

}
void C_Resolver::CorrectAnimations( C_BasePlayer* Player, LagRecord_t* m_Record, LagRecord_t* m_PrevRecord )
{
	/* CANCELED IN FIRST RELEASE VERSION */
	return;

}
float C_Resolver::BuildMoveYaw( C_BasePlayer* Player, float flFootYaw )
{
	/* m_PlayerAnimationStateCSGO( )->m_flMoveYawIdeal */
	float m_flMoveYawIdeal = 0.0f;

	/* Rebuild m_flMoveYawIdeal */
	float flVelocityLengthXY = Player->m_vecVelocity( ).Length2D( );
	if ( flVelocityLengthXY > 0 && Player->m_fFlags( ) & FL_ONGROUND )
	{
		// convert horizontal velocity vec to angular yaw
		float flRawYawIdeal = ( atan2( -Player->m_vecVelocity( )[ 1 ], -Player->m_vecVelocity( )[ 0 ] ) * M_RADPI );
		if ( flRawYawIdeal < 0.0f )
			flRawYawIdeal += 360.0f;

		m_flMoveYawIdeal = Math::AngleNormalize( Math::AngleDiff( flRawYawIdeal, flFootYaw ) );
	}

	/* Return m_flMoveYaw */
	return m_flMoveYawIdeal;
}
float C_Resolver::BuildPlaybackRate( C_BasePlayer* Player, int nSide )
{
	/* Move sequence */
	const int nMoveSequence = Player->GetAnimationLayers( )[ ANIMATION_LAYER_MOVEMENT_MOVE ].m_nSequence;

	/* flMoveCycleRate Value */
	float flMoveCycleRate = 0.0f;

	/* Rebuild flMoveCycleRate */
	float flVelocityLengthXY = Player->m_vecVelocity( ).Length2D( );
	if ( flVelocityLengthXY > 0 )
	{
		flMoveCycleRate = Player->GetLayerSequenceCycleRate( &Player->GetAnimationLayers( )[ ANIMATION_LAYER_MOVEMENT_MOVE ], nMoveSequence );
		flMoveCycleRate *= flVelocityLengthXY / fmax( Player->GetSequenceMoveDist( nMoveSequence ) / ( 1.0f / flMoveCycleRate ), 0.001f );
		flMoveCycleRate *= Math::Lerp( Player->GetAnimationState( )->m_flWalkToRunTransition, 1.0f, CSGO_ANIM_RUN_ANIM_PLAYBACK_MULTIPLIER );
	}

	/* Calculate the final m_flPlaybackRate */
	return flMoveCycleRate * SDK::Interfaces::GlobalVars->m_flIntervalPerTick;	
}