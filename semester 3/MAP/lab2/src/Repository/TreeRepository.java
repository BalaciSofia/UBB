package Repository;
import Model.TreeNotFoundEx;
import Model.Tree;
public class TreeRepository implements Repository {
    private Tree[] trees;
    private int count;

    public TreeRepository(){
        this.trees = new Tree[1];
        this.count = 0;
    }

    @Override
    public int getCount(){
        return this.count;
    }

    @Override
    public void addTree(Tree newtree){
        if(count>=trees.length){
            if (this.count>=1000) System.out.println("repo is full");
            else{
               Tree[] newtrees = new Tree[this.count*2];
                System.arraycopy(this.trees,0,newtrees,0,this.count);
                this.trees = newtrees;
            }
        }
        this.trees[count++] = newtree;
    }

    @Override
    public void deleteTree(Tree deletetree) throws TreeNotFoundEx {
        int newCount = 0;
        boolean deleted = false;
       Tree[] newtrees = new Tree[trees.length];
        for (int i = 0; i < count; i++) {
            if (!deleted && trees[i].getClass() == deletetree.getClass() && trees[i].getAge() == deletetree.getAge()) {
                deleted = true;
                continue;
            }
            newtrees[newCount++] = trees[i];
        }
        if(!deleted){
            throw new TreeNotFoundEx("Tree not found");
        }
        else{
            System.arraycopy(newtrees, 0, this.trees, 0, newCount);
            this.count = newCount;
        }
    }

    @Override
    public Tree getTree(int index){
        return this.trees[index];
    }

    @Override
    public Tree[] treeRepository(){
       Tree[] res=new Tree[count];
        System.arraycopy(this.trees,0,res,0,this.count);
        return res;
    }
}
