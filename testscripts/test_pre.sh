#! /bin/sh
# Preinit tests

ret=0
cd "$T3_OUT"
for i in preinit
do
    echo "Preinit test: $i"
    $TESTPROGS/test_prs_top "$T3_DAT/$i.t" "$T3_OUT/$i.t3" > "$T3_OUT/$i.log" 2>"$T3_OUT/$i.err"
    cat "$T3_OUT/$i.err" >> "$T3_OUT/$i.log"
    $TESTPROGS/t3pre "$T3_OUT/$i.t3" "$T3_OUT/${i}_pre.t3" >> "$T3_OUT/$i.log" 2>"$T3_OUT/$i.err"
    cat "$T3_OUT/$i.err" >> "$T3_OUT/$i.log"
    $TESTPROGS/test_exec -cs cp437 "$T3_OUT/${i}_pre.t3" >> "$T3_OUT/$i.log" 2>"$T3_OUT/$i.err"
    cat "$T3_OUT/$i.err" >> "$T3_OUT/$i.log"
    rm "$T3_OUT/$i.err"
    if $SCRIPTS/test_diff.sh "$i"; then
        :
    else
        ret=1
    fi
done
exit $ret
