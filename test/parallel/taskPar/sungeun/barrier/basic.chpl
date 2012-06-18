use Barrier;
use BlockDist;

config const numTasks = 31;
config const numRemoteTasks = numLocales*11;

proc localTest(b, numTasks) {
  const barSpace = 0..#numTasks;
  var A: [barSpace] int = -1;
  coforall t in barSpace do {
    A[t] = t;
    b.barrier();
    if t==0 then writeln(A);
  }
}

proc remoteTest(b, numRemoteTasks) {
  const barSpace = 0..#numRemoteTasks;
  var A: [[barSpace] dmapped new dmap(new Block([barSpace]))] int = barSpace;
  var B: [[barSpace] dmapped new dmap(new Block([barSpace]))] int = -1;
  coforall t in barSpace do on A.domain.dist.idxToLocale(t) {
    B[t] = A[t];
    b.barrier();
    if t==0 then writeln(B);
  }
}


var b: Barrier(reusable=false) = new Barrier(numTasks);
localTest(b, numTasks);

b.reset(numRemoteTasks);
remoteTest(b, numRemoteTasks);

var sb1 = new sBarrier(numTasks);
localTest(sb1, numTasks);

var sb2 = new sBarrier(numRemoteTasks);
remoteTest(sb2, numRemoteTasks);

