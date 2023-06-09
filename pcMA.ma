[top]
components : pc@Pc 
out : DOut
out : pc_cam
in : tr_ts
in : pcI
in : cam_pc
Link : tr_ts tr_ts@Pc
Link : pcI pcI@Pc
Link : cam_pc cam_pc@Pc
Link : DOut@Pc DOut
Link : pc_cam@Pc pc_cam

[pc]
preparation : 00:00:00:010 
wait : 00:00:10:000 