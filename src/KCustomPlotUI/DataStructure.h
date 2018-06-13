/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataStructure.h
 * Author: root
 *
 * Created on January 17, 2018, 9:31 PM
 */

#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <stdint-gcc.h>
#include "DefineParameter.h"

typedef struct __attribute__((packed)) T_AXIS_TARGETINFO
{
    double position_p_gain;
    double position_d_gain;
    double position_i_gain;
    
    double target_degree;
    double target_torque;
}AXIS_TARGETINFO,*PAXIS_TARGETINFO;



typedef struct __attribute__((packed)) T_CONTROL_DATA
{
    int                 control_mode;
    AXIS_TARGETINFO     axis_target_info[AXIS_COUNT];
    int                 Update_CCT;
    double target_data[20];

    
}CONTROL_DATA,*PCONTROL_DATA;



typedef struct __attribute__((packed)) T_JOINTSTATE_DATA
{
    double joint_position;
    double joint_velocity;
    
}JOINTSTATE_DATA,*PJOINTSTATE_DATA;



typedef struct __attribute__((packed)) T_XYZ_DATA
{
    double x;
    double y;
    double z;
    
}XYZ_DATA, *PXYZ_DATA;



typedef struct __attribute__((packed)) T_BASE_DATA
{
    XYZ_DATA           position;
    XYZ_DATA           orientation;
    XYZ_DATA           linear_velocity;
    XYZ_DATA           algular_velocity;
    
}BASE_DATA,*PBASE_DATA;


typedef struct __attribute__((packed)) T_FT_DATA
{
    double fx;
    double fy;
    double fz;
    double tx;
    double ty;
    double tz;
    
}FT_DATA,*PFT_DATA;



typedef struct __attribute__((packed)) T_FT_SENSORS_DATA
{
    FT_DATA ft_data[FT_COUNT];
    
}FT_SENSORS_DATA,*PFT_SENSORS_DATA;



typedef struct __attribute__((packed)) T_SENSORED_DATA
{
    JOINTSTATE_DATA         axis_joint_state[AXIS_COUNT];
    BASE_DATA               base_state;
    FT_SENSORS_DATA         ft_sensor;
    int Update_LBSIF;
    
}SENSORED_DATA,*PSENSORED_DATA;



typedef struct __attribute__((packed)) T_LOWERBODYSIMALGO_DATA
{
    CONTROL_DATA    control_data;
    SENSORED_DATA   sensored_data;
    
}LOWERBODYSIMALGO_DATA, *PLOWERBODYSIMALGO_DATA;



typedef struct __attribute__((packed)) T_PLAYER_DATA
{
    JOINTSTATE_DATA         axis_joint_state[AXIS_COUNT];
    BASE_DATA               base_state;
    
}PLAYER_DATA,*PPLAYER_DATA;
/**Computed Algorithm target degree in each Axis 
 */

#endif /* DATASTRUCTURE_H */

