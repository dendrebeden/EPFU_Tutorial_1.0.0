struct tiles rotation(int tile_id,int tile_rotation)
    {
        struct tiles *answer;
        int tmp;
        
        
        answer->tileid = tile[tileid]->tileid;
        answer->name = tile[tileid]->name;
        answer->isTemple = tile[tileid]->isTemple;
        answer->crossRoads = tile[tileid]->crossRoads;
        answer->bonus = tile[tileid]->bonus;
        answer->top = tile[tileid]->top;
        answer->right = tile[tileid]->right;
        answer->left = tile[tileid]->left;
        answer->bottom = tile[tileid]->bottom;
            
        for (int i = 1; i < tile_rotation; i++) {
            tmp = answer->top;
            answer->top = answer->left;
            answer->left = answer->bottom;
            answer->bottom = answer->right;
            answer->right = tmp;
        }
        
        return answer;
    }
