[top]
components : pc@Pc
components : cameras@Cameras

out : pcI tr_ts
out : DOut

Link : tr_ts tr_ts@pc
Link : DOut@pc DOut 
Link : pcI pcI@pc
Link : pc_cam@pc pc_cam@cameras
Link : cam_pc@cameras cam_pc@pc


[pc]
preparation : 00:00:00:010 
wait : 00:00:010:000

[cameras]
preparation : 00:00:06:000