int LEFT, r[MAXV]; bool seen[MAXV]; VI AdjList[MAXV];
bool can_match(int u) {
    for (auto & v : AdjList[u]) {
        if (!seen[v]) {
            seen[v] = true;
            if (r[v] < 0 || can_match(r[v])) {
                r[v] = u; return true;
            }
        }
    } return false;
}
int max_matching() {
    memset(r, -1, sizeof r);
    int ans = 0;
    for (int u=0 ; u<LEFT ; u++) {
        memset(seen, 0, sizeof seen);
        if (can_match(u)) ans++;
    } return ans;
}