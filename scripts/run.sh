p=../dist/Debug/GNU-Linux/memo100
a=--memo_caching_strategy
#strategy=linear_probe_hashing
strategy=lru
b=--memo_lru_queue_size
qs=5
c=--memo_cache_size
cs=6
vlp=--memo_key_length
vl=8
klp=--memo_value_length
kl=8
$p $a $strategy $b $qs $c $cs $vlp $vl $klp $kl
