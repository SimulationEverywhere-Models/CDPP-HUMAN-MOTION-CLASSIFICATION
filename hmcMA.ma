[top]
components : motion_capture_system
components : preprocessor@Preprocessor
components : classifier@Classifier

out : result
in : init

Link : init pcI@motion_capture_system
Link : DOut@motion_capture_system DIn@preprocessor
Link : DP@preprocessor DP@classifier
Link : result@classifier result
Link : trainAcc@classifier tr_ts@motion_capture_system

[preprocessor]
preparation : 00:00:05:000

[classifier]
preparation : 00:00:03:000 

[motion_capture_system]
components : pc@Pc
components : cameras@Cameras

in : tr_ts pcI
out : DOut

Link : tr_ts tr_ts@pc
Link : pcI pcI@pc
Link : DOut@pc DOut
Link : pc_cam@pc pc_cam@cameras
Link : cam_pc@cameras cam_pc@pc 

[pc]
preparation : 00:00:00:010 
wait : 00:00:010:000 

[cameras]
preparation : 00:00:06:000
