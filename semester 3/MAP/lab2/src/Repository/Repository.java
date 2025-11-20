package Repository;

import Model.TreeNotFoundEx;
import Model.Tree;

public interface Repository {
    public int getCount();
    public void addTree(Tree t);
    public void deleteTree(Tree t) throws TreeNotFoundEx;
    public Tree getTree(int index);
    public Tree[]  treeRepository();
}
