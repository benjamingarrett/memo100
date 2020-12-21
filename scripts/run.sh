p=../dist/Debug/GNU-Linux/memo100
etf=--mbt_execution_trace_fname
et=execution_trace.log
mck=--memo_cuckoo_k
mc=4
mkl=--memo_key_length
mk=8
mvl=--memo_value_length
ml=8


function do_session {
  alg=$1
  n=$2
  k=$3
  d=$4
  a=$5
  $p --memo_caching_strategy $alg --memo_cache_size $n --memo_k_timestamps $k --memo_d_recent_timestamps $d --memo_a_items_per_timestamp_factor $a $etf $et $mck $mc $mkl $mk $mvl $ml
}

do_session nru_d_drunken_absolute 16 6 5 0.1875
