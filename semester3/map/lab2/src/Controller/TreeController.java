package Controller;
import Model.*;
import Repository.Repository;
import Repository.TreeRepository;

public class TreeController {
    private Repository repo;

    public TreeController(Repository repo){
        this.repo = new TreeRepository();
    }

    public void populate(){
        AppleTree a = new AppleTree(1);
        AppleTree b = new AppleTree(5);
        PearTree d = new PearTree(3);
        PearTree c = new PearTree(4);
        PearTree e = new PearTree(6);
        CherryTree f = new CherryTree(2);
        CherryTree g = new CherryTree(3);
        CherryTree h = new CherryTree(1);
        this.repo.addTree(a);
        this.repo.addTree(b);
        this.repo.addTree(c);
        this.repo.addTree(d);
        this.repo.addTree(e);
        this.repo.addTree(f);
        this.repo.addTree(g);
        this.repo.addTree(h);
    }

    public Tree[] OldTrees(){
        Tree[] oldtrees = new Tree[20];
        int c=0;
        for(Tree t:this.repo.treeRepository()){
            if(t.getAge()>=3)
                oldtrees[c++]=t;
        }
        Tree[] res = new Tree[c];
        System.arraycopy(oldtrees,0,res,0,c);
        return res;
    }

    public Tree[] getTrees(){
        Tree[] res=new Tree[this.repo.getCount()];
        System.arraycopy(this.repo.treeRepository(),0,res,0,this.repo.getCount());
        return res;
    }

    public void addAppleTree(int age){
        Tree a = new AppleTree(age);
        this.repo.addTree(a);
    }

    public void addCherryTree(int age){
        Tree c = new CherryTree(age);
        this.repo.addTree(c);
    }

    public void addPearTree(int age){
        Tree p = new PearTree(age);
        this.repo.addTree(p);
    }

    public void deleteTree(Tree T) throws TreeNotFoundEx {
            this.repo.deleteTree(T);
    }
}
