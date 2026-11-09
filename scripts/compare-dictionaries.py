"""Compare validated DOS Pascal word/topic records, retaining duplicates and order."""
import argparse, collections, hashlib, json
from pathlib import Path

def read(path):
    b=path.read_bytes()
    assert 0<b[0]<=20
    count=int(b[1:1+b[0]])
    assert len(b)==21+42*count, (path, len(b),count)
    rows=[]
    for i in range(count):
        fields=[]
        for p in (21+42*i,42+42*i):
            assert 0<b[p]<=20,(path,i,b[p])
            fields.append(bytes((c-32)&255 for c in b[p+1:p+1+b[p]]).decode('cp866'))
        rows.append(tuple(fields))
    return rows

def compare(old,new):
    a,b=read(old),read(new); raw_old,raw_new=old.read_bytes(),new.read_bytes(); padding_changes=0; content_changes=0
    for i in range(min(len(a),len(b))):
        for off in (21+42*i,42+42*i):
            for j in range(21):
                if raw_old[off+j]!=raw_new[off+j]:
                    if j<=max(raw_old[off],raw_new[off]):content_changes+=1
                    else:padding_changes+=1
    ca,cb=collections.Counter(a),collections.Counter(b)
    aw,bw=set(w for w,t in a),set(w for w,t in b)
    return dict(old_sha256=hashlib.sha256(old.read_bytes()).hexdigest(),new_sha256=hashlib.sha256(new.read_bytes()).hexdigest(),old_count=len(a),new_count=len(b),common_pairs=len(set(a)&set(b)),old_unique=len(ca),new_unique=len(cb),added_pairs=list((cb-ca).elements()),removed_pairs=list((ca-cb).elements()),added_words=sorted(bw-aw),removed_words=sorted(aw-bw),changed_topics=[dict(word=w,old=sorted({t for x,t in a if x==w}),new=sorted({t for x,t in b if x==w})) for w in sorted(aw&bw) if {t for x,t in a if x==w}!={t for x,t in b if x==w}],old_duplicates=[[*p,n] for p,n in ca.items() if n>1],new_duplicates=[[*p,n] for p,n in cb.items() if n>1],prefix_unchanged=b[:len(a)]==a,raw_record_prefix_identical=raw_old[21:]==raw_new[21:len(raw_old)],prefix_content_byte_changes=content_changes,prefix_padding_byte_changes=padding_changes)
if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('old',type=Path);p.add_argument('new',type=Path);p.add_argument('output',type=Path);args=p.parse_args()
    result=compare(args.old,args.new);args.output.parent.mkdir(parents=True,exist_ok=True);args.output.write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n');print(json.dumps({k:v for k,v in result.items() if not isinstance(v,list)},ensure_ascii=False));print({k:len(v) for k,v in result.items() if isinstance(v,list)})
