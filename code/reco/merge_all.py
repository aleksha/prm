
def merge_two_files(f1, f2, fm):
    f_scat = open(f1 ,"r")
    f_init = open(f2 ,"r")
    f_merg = open(fm ,"w")
    e_init = 0
    e_scat = 0
    EVENT  = 0
    not_first  = False
    for l_init in f_init:
        w_init = l_init[:-1].split(" ")
        e_init = int( w_init[0] )
        if e_init > EVENT:
            if not_first:
                f_merg.write( l_scat ) # write prev line
            not_first = True
            while e_scat < e_init:
                l_scat = f_scat.readline()
                if len(l_scat)<1:
                    break
                e_scat = int( l_scat[:-1].split(" ")[0] )
                f_merg.write( l_scat ) # write
            EVENT += 1
        f_merg.write( l_init )
    # foa last event
    f_merg.write( l_scat ) # write prev line
    while e_scat < e_init:
        l_scat = f_scat.readline()
        e_scat = l_scat[:-1].split(" ")[0]
        f_merg.write( l_scat ) # write
    # -----
    f_init.close()
    f_merg.close()
    f_scat.close()


print("MERGE out.data FILES")
print("    init + scat  = temp1")
merge_two_files( f1="init/out.data", f2="scat/out.data", fm="temp1.data");
print("    temp1 + beam = out")
merge_two_files( f1="temp1.data", f2="beam/out.data", fm="out.data");

print("MERGE tpc.data FILES")
print("    init + scat  = temp2")
merge_two_files( f1="init/tpc.data", f2="scat/tpc.data", fm="temp2.data");
print("    prot + beam = temp3")
merge_two_files( f1="prot/tpc.data", f2="beam/tpc.data", fm="temp3.data");
print("    temp2 + temp3 = tpc")
merge_two_files( f1="temp2.data", f2="temp3.data", fm="tpc.data");
