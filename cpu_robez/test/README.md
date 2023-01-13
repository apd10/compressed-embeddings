# steps to run.
1. create a new empty environ with conda / pip with latest python (3.8/3.9)
2. install pytorch using pip/conda in accordance with pytorch.org installation
3. cd into this folder, run 
```
python3 setup.py install
```
4. run
```
taskset -c <num-cores> python3 python_interface.py
```



processor info. (64 cores per node. 2 nodes)
```
processor       : 0
vendor_id       : AuthenticAMD
cpu family      : 23
model           : 49
model name      : AMD EPYC 7742 64-Core Processor
stepping        : 0
microcode       : 0x8301034
cpu MHz         : 1498.870
cache size      : 512 KB
physical id     : 0
siblings        : 64
core id         : 0
cpu cores       : 64
apicid          : 0
initial apicid  : 0
fpu             : yes
fpu_exception   : yes
cpuid level     : 16
wp              : yes
flags           : fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ht syscall nx mmxext fxsr_opt pdpe1gb rdtscp lm constant_tsc rep_good nopl nonstop_tsc cpuid extd_apicid aperfmperf pni pclmulqdq monitor ssse3 fma cx16 sse4_1 sse4_2 movbe popcnt aes xsave avx f16c rdrand lahf_lm cmp_legacy svm extapic cr8_legacy abm sse4a misalignsse 3dnowprefetch osvw ibs skinit wdt tce topoext perfctr_core perfctr_nb bpext perfctr_llc mwaitx cpb cat_l3 cdp_l3 hw_pstate sme ssbd mba sev ibrs ibpb stibp vmmcall fsgsbase bmi1 avx2 smep bmi2 cqm rdt_a rdseed adx smap clflushopt clwb sha_ni xsaveopt xsavec xgetbv1 xsaves cqm_llc cqm_occup_llc cqm_mbm_total cqm_mbm_local clzero irperf xsaveerptr wbnoinvd arat npt lbrv svm_lock nrip_save tsc_scale vmcb_clean flushbyasid decodeassists pausefilter pfthreshold avic v_vmsave_vmload vgif umip rdpid overflow_recov succor smca
bugs            : sysret_ss_attrs spectre_v1 spectre_v2 spec_store_bypass
bogomips        : 4499.85
TLB size        : 3072 4K pages
clflush size    : 64
cache_alignment : 64
address sizes   : 43 bits physical, 48 bits virtual
power management: ts ttp tm hwpstate cpb eff_freq_ro [13] [14]
```
batch size = 1024 
dimension = 128
Before fix:
1 CPU 
| implementation | time 1024x128|
|----------------|--------------|
| pure python    | 2.12 ms      |
| cpp interface  | 274ms        |
| python interface| 268ms       |

After fix 
1CPU
Run the following for the comparison
```
taskset -c 5 python3 python_interface.py
```
|desc|function|time|
|----------------|--------------|--------------|
|pure python | par_idx_py | 2.71ms|
|omp cpp | get_idx_p | 1.08ms|
|single cpp| get_idx_s | 0.21ms|
|single cpp(tabulation| s_tab | 0.14ms|
