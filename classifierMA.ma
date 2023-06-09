[top]
components : classifier@Classifier 
out : result
out : trainAcc
in : DP
Link : DP DP@classifier
Link : result@classifier result
Link : trainAcc@classifier trainAcc

[classifier]
preparation : 00:00:03:000 