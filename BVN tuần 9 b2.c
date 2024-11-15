#include <stdio.h>
#include <stdlib.h>

struct Node {
    int heSo; 
    int bac;    
    struct Node* tiepTheo; 
};

struct Node* taoNode(int heSo, int bac) {
    struct Node* nutMoi = (struct Node*)malloc(sizeof(struct Node));
    nutMoi->heSo = heSo;
    nutMoi->bac = bac;
    nutMoi->tiepTheo = NULL;
    return nutMoi;
}

void chenDau(struct Node** daThuc, int heSo, int bac) {
    struct Node* nutMoi = taoNode(heSo, bac);
    nutMoi->tiepTheo = *daThuc;
    *daThuc = nutMoi;
}

void chenSau(struct Node* truoc, int heSo, int bac) {
    if (truoc == NULL) return;
    struct Node* nutMoi = taoNode(heSo, bac);
    nutMoi->tiepTheo = truoc->tiepTheo;
    truoc->tiepTheo = nutMoi;
}

void xoaNode(struct Node** daThuc, struct Node* hienTai) {
    if (hienTai == NULL) return;

    if (*daThuc == hienTai) {
        *daThuc = hienTai->tiepTheo;
    } else {
        struct Node* truoc = *daThuc;
        while (truoc->tiepTheo != hienTai) {
            truoc = truoc->tiepTheo;
        }
        truoc->tiepTheo = hienTai->tiepTheo;
    }
    free(hienTai);
}

void chenHangTu(struct Node** daThuc, int heSo, int bac) {
    if (heSo == 0) return;

    if (*daThuc == NULL || (*daThuc)->bac < bac) {
        chenDau(daThuc, heSo, bac);
        return;
    }

    struct Node* hienTai = *daThuc;
    struct Node* truoc = NULL;

    while (hienTai != NULL && hienTai->bac > bac) {
        truoc = hienTai;
        hienTai = hienTai->tiepTheo;
    }

    if (hienTai != NULL && hienTai->bac == bac) {
        hienTai->heSo += heSo;
        if (hienTai->heSo == 0) {
            xoaNode(daThuc, hienTai);
        }
        return;
    }

    if (truoc == NULL) {
        chenDau(daThuc, heSo, bac);
    } else {
        chenSau(truoc, heSo, bac);
    }
}

void nhapDaThuc(struct Node** daThuc) {
    int heSo, bac;
    printf("Nhap cac he so va bac cua tung hang tu (nhap he so 0 de ket thuc):\n");
    while (1) {
        printf("Nhap he so: ");
        scanf("%d", &heSo);
        if (heSo == 0) break;
        printf("Nhap bac cua x: ");
        scanf("%d", &bac);
        chenHangTu(daThuc, heSo, bac);
    }
}

void inDaThuc(struct Node* daThuc) {
    struct Node* hienTai = daThuc;
    if (hienTai == NULL) {
        printf("0\n");
        return;
    }
    while (hienTai != NULL) {
        if (hienTai->heSo > 0 && hienTai != daThuc) {
            printf("+");
        }
        printf("%dx^%d ", hienTai->heSo, hienTai->bac);
        hienTai = hienTai->tiepTheo;
    }
    printf("\n");
}

struct Node* congDaThuc(struct Node* daThuc1, struct Node* daThuc2) {
    struct Node* ketQua = NULL;

    while (daThuc1 != NULL || daThuc2 != NULL) {
        int heSo = 0;
        int bac;

        if (daThuc1 != NULL && (daThuc2 == NULL || daThuc1->bac > daThuc2->bac)) {
            heSo = daThuc1->heSo;
            bac = daThuc1->bac;
            daThuc1 = daThuc1->tiepTheo;
        } else if (daThuc2 != NULL && (daThuc1 == NULL || daThuc2->bac > daThuc1->bac)) {
            heSo = daThuc2->heSo;
            bac = daThuc2->bac;
            daThuc2 = daThuc2->tiepTheo;
        } else {
            heSo = daThuc1->heSo + daThuc2->heSo;
            bac = daThuc1->bac;
            daThuc1 = daThuc1->tiepTheo;
            daThuc2 = daThuc2->tiepTheo;
        }

        chenHangTu(&ketQua, heSo, bac);
    }

    return ketQua;
}

int main() {
    struct Node* daThuc1 = NULL;
    struct Node* daThuc2 = NULL;

    printf("Nhap da thuc f(x):\n");
    nhapDaThuc(&daThuc1);
    
    printf("Nhap da thuc g(x):\n");
    nhapDaThuc(&daThuc2);

    printf("f(x) = ");
    inDaThuc(daThuc1);
    printf("g(x) = ");
    inDaThuc(daThuc2);
    
    struct Node* tongDaThuc = congDaThuc(daThuc1, daThuc2);
    printf("h(x) = f(x) + g(x) = ");
    inDaThuc(tongDaThuc);
    
    return 0;
}
