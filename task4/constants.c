#include "constants.h"
#include <math.h>
#include <stdio.h>

Status e_ryad(double eps, double *e) {
    if (eps <= 0) {
        printf("Эпсилон должен быть > 0\n");
        return STATUS_INVALID_EPS;
    }
    if (!e) return STATUS_INVALID_EPS;

    double sum = 0, slag = 1;
    int n = 0;

    while (slag > eps) {
        sum += slag;
        n++;
        slag /= n;
    }

    *e = sum;
    return STATUS_OK;
}

Status e_lim(double eps, double *e) {
    if (eps <= 0) {
        printf("Эпсилон должен быть > 0\n");
        return STATUS_INVALID_EPS;
    }
    if (!e) return STATUS_INVALID_EPS;

    double nprev = 0, ncur = 2;
    int n = 1;

    while (1) {
        ncur = pow(1.0 + 1.0 / n, n);
        if (fabs(ncur - nprev) < eps) break;
        nprev = ncur;
        n++;
        if (n > 1000000) return STATUS_NO_LIM;
    }

    *e = ncur;
    return STATUS_OK;
}

Status e_newton(double eps, double *e) {
    if (eps <= 0) {
        printf("Эпсилон должен быть > 0\n");
        return STATUS_INVALID_EPS;
    }
    if (!e) return STATUS_INVALID_EPS;

    double dx, x = 2.0;
    do {
        double f = log(x) - 1.0;
        double df = 1.0 / x;
        dx = -f / df;
        x += dx;
    } while (fabs(dx) >= eps);

    *e = x;
    return STATUS_OK;
}

Status pi_ryad(double eps, double *pi) {
    if (eps <= 0) {
        printf("Эпсилон должен быть > 0\n");
        return STATUS_INVALID_EPS;
    }
    if (!pi) return STATUS_INVALID_EPS;

    double sum = 0, slag = 1;
    int n = 1;

    while (fabs(slag) > eps) {
        sum += slag;
        n++;
        slag = (n % 2 == 0 ? -1.0 : 1.0) / (2 * n - 1);
    }

    *pi = 4 * sum;
    return STATUS_OK;   
}

Status pi_lim(double eps, double *pi) {
    if (eps <= 0) {
        printf("Эпсилон должен быть > 0\n");
        return STATUS_INVALID_EPS;
    }
    if (!pi) return STATUS_INVALID_EPS;

    double ncur, nprev = 0;
    int n = 1;

    while (1) {
        double ln_ncur = 4 * n * log(2);
        for (int i = 1; i <= n; ++i) {
            ln_ncur += 4.0 * log(i);
        }
        ln_ncur -= log(n);

        for (int i = 1; i <= 2 * n; ++i) {
            ln_ncur -= 2.0 * log(i);
        }
        ncur = exp(ln_ncur);
        if (fabs(ncur - nprev) < eps) break;
        ++n;
        nprev = ncur;
        
        if (n > 1000) return STATUS_NO_LIM;
    }

    *pi = ncur;
    return STATUS_OK;
}

Status pi_newton(double eps, double *pi) {
    if (eps <= 0) {
        printf("Эпсилон должен быть > 0\n");
        return STATUS_INVALID_EPS;
    }
    if (!pi) return STATUS_INVALID_EPS;

    double x = 3.0, dx;
    do {
        double f = cos(x) + 1;
        double df = -1 * sin(x);
        dx = -f / df;
        x += dx;
    } while (fabs(dx) >= eps);

    *pi = x;
    return STATUS_OK;
}

Status ln2_ryad(double eps, double *ln2) {
    if (eps <= 0) {
        printf("Эпсилон должен быть > 0\n");
        return STATUS_INVALID_EPS;
    }
    if (!ln2) return STATUS_INVALID_EPS;

    double sum = 0, slag = 1;
    int n = 1;

    while (fabs(slag) > eps) {
        sum += slag;
        n++;
        slag = (n % 2 == 0 ? -1.0 : 1.0) / n;
    }

    *ln2 = sum;
    return STATUS_OK;   
}

Status ln2_lim(double eps, double *ln2) {
    if (eps <= 0) {
        printf("Эпсилон должен быть > 0\n");
        return STATUS_INVALID_EPS;
    }
    if (!ln2) return STATUS_INVALID_EPS;

    double ncur, nprev = 0;;
    int n = 1;

    while (1) {
        ncur = n * (pow(2.0, 1.0 / n) - 1);

        if (fabs(ncur - nprev) < eps) break;

        ++n;
        nprev = ncur;

        if (n > 100000) return STATUS_NO_LIM;
    }

    *ln2 = ncur;
    return STATUS_OK;
}

Status ln2_newton(double eps, double *ln2) {
    if (eps <= 0) {
        printf("Эпсилон должен быть > 0\n");
        return STATUS_INVALID_EPS;
    }
    if (!ln2) return STATUS_INVALID_EPS;

    double x = 1.0, dx;
    do {
        double f = exp(x) - 2;
        double df = exp(x);
        dx = -f / df;
        x += dx;
    } while (fabs(dx) >= eps);

    *ln2 = x;
    return STATUS_OK;   
}

Status sqrt2_ryad(double eps, double *sqrt2) {
    if (eps <= 0) {
        printf("Эпсилон должен быть > 0\n");
        return STATUS_INVALID_EPS;
    }
    if (!sqrt2) return STATUS_INVALID_EPS;

    double proizv = 1.0, mn = pow(2.0, pow(2.0, -2.0));
    double next = proizv * mn;
    int k = 2;

    while (fabs(next - proizv) > eps) {
        proizv = next;
        k++;
        mn = pow(2.0, pow(2.0, -k));
        next *= mn;

        if (k > 1000) return STATUS_NO_LIM;
    }

    *sqrt2 = proizv;
    return STATUS_OK; 
}

Status sqrt2_lim(double eps, double *sqrt2) {
    if (eps <= 0) {
        printf("Эпсилон должен быть > 0\n");
        return STATUS_INVALID_EPS;
    }
    if (!sqrt2) return STATUS_INVALID_EPS;

    double nprev = -0.5, ncur;
    int n = 1;

    while (1) {
        ncur = nprev - nprev * nprev / 2 + 1;

        if (fabs(ncur - nprev) < eps) break;

        ++n;
        nprev = ncur;

        if (n > 100000) return STATUS_NO_LIM;
    }

    *sqrt2 = ncur;
    return STATUS_OK;
}

Status sqrt2_newton(double eps, double *sqrt2) {
    if (eps <= 0) {
        printf("Эпсилон должен быть > 0\n");
        return STATUS_INVALID_EPS;
    }
    if (!sqrt2) return STATUS_INVALID_EPS;

    double x = 1.0, dx;
    do {
        double f = x * x - 2;
        double df = 2 * x;
        dx = -f / df;
        x += dx;
    } while (fabs(dx) >= eps);

    *sqrt2 = x;
    return STATUS_OK;   
}

Status y_ryad(double eps, double *y) {
    if (eps <= 0) {
        printf("Эпсилон должен быть > 0\n");
        return STATUS_INVALID_EPS;
    }
    if (!y) return STATUS_INVALID_EPS;

    double pi;
    Status status = pi_newton(0.00001, &pi);
    if (status != STATUS_OK) return status;
    double sum = 0;
    int k = 2;
    // сходится очень медленно
    while (k < 5000000) {
        int sqrt_floor_k = (int)sqrt(k);

        double temp = 1.0 / (sqrt_floor_k * sqrt_floor_k) - 1.0 / k;

        sum += temp;
        k++;
    }

    *y = sum - pi * pi / 6.0;
    return STATUS_OK; 
}

Status y_lim(double eps, double *y) {
    if (eps <= 0) {
        printf("Эпсилон должен быть > 0\n");
        return STATUS_INVALID_EPS;
    }
    if (!y) return STATUS_INVALID_EPS;
    
    double nprev = 0, ncur, sum; 
    int m = 2;

    while (1) {
        sum = 0;
        for (int k = 1; k <= m; ++k) {
            double Cmk = 1.0;
            for (int i = 1; i <= k; ++i) {
                Cmk *= (double)(m - i + 1) / i;
            }

            double ln_k = 0;
            for (int i = 1; i <= k; ++i) {
                ln_k += log(i);       
            }

            double tmp = Cmk * (k % 2 == 0 ? 1.0 : -1.0) / k * ln_k;
            sum += tmp;
        }

        if (fabs(sum - nprev) < eps) break;

        nprev = sum;
        ++m;
        if (m > 200) return STATUS_NO_LIM;
    }

    *y = sum;
    return STATUS_OK;
}

Status y_newton(double eps, double *y) {
    if (eps <= 0) {
        printf("Эпсилон должен быть > 0\n");
        return STATUS_INVALID_EPS;
    }
    if (!y) return STATUS_INVALID_EPS;

    int t = 2;
    double nprev = 0;

    while(1) {
        double ln_t = log(t);
        double proizv = 1.0;   

        for (int p = 2; p <= t; ++p) {
            int prime = 1;
            for (int i = 2; i * i <= p; ++i) {
                if (p % i == 0) {
                    prime = 0;
                    break;
                }  
            }
            if (prime) {
                proizv *= (double)(p - 1) / p;
            }
        }

        double a = ln_t * proizv;

        if (a <= 0) {
            ++t;
            continue;
        }

        if (fabs(a - nprev) < eps) {
            *y = -log(a);
            return STATUS_OK;
        }
        nprev = a;
        ++t;
        if (t > 5000) return STATUS_NO_LIM;
    }
}