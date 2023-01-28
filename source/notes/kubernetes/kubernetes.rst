
===
k0s
===
* YT: `K0S Kubernetes Demo <https://youtube.com/playlist?list=PL34sAs7_26wPu4YL9wW1HLwtssQx1EgS->`_
* YT: `Hands-on Introduction to K0s <https://www.youtube.com/watch?v=pXbJwlUDnUI>`_


Install
=======

Download ``k0s`` binary to ``/usr/local/bin/k0s``:

.. code-block:: sh

    curl -sSLf https://get.k0s.sh | sudo sh
    # or
    curl -sSLf https://get.k0s.sh | sudo K0S_VERSION=v1.21.2+k0s.0 DEBUG=true sh


Install k0s as a systemd service.
Can install a worker, a controller, or a single node (controller+worker).
This will create a ``/etc/systemd/system/k0scontroller.service``
running a ``/usr/local/bin/k0s controller --single=true`` command:

.. code-block:: sh

    sudo k0s install controller --single
    # or, with explicitly specified (custom) config file
    k0s default-config > k0s.yaml
    sudo k0s install controller -c ${PWD}/k0s.yaml

    # Show service file created
    systemctl list-unit-files |grep k0s
    systemctl cat k0scontroller.service

Start a service:

.. code-block:: sh

    sudo k0s start
    # or
    systemctl start k0scontroller.service

    # Check status (takes a 1-2 minutes)
    sudo k0s status

    # Can now use kubectl
    sudo k0s kubectl get nodes


Install via k0sctl
==================

.. code-block:: sh

    wget -O ~/bin/k0sctl https://github.com/k0sproject/k0sctl/releases/download/v0.12.5/k0sctl-linux-x64
    chmod +x ~/bin/k0sctl
    # or
    nix-env -i k0sctl


========
Minikube
========

.. code-block:: sh

    curl -Lo ~/bin/minikube https://storage.googleapis.com/minikube/releases/latest/minikube-linux-amd64
    chmod +x ~/bin/minikube


===
k3s
===
* `A visual guide on troubleshooting kubernetes deployments <https://learnk8s.io/a/a-visual-guide-on-troubleshooting-kubernetes-deployments/troubleshooting-kubernetes.en_en.v3.pdf>`_

Install
=======
* `k3s: High Availability with Embedded DB <https://docs.k3s.io/installation/ha-embedded>`_
* `k3s: Architecture <https://docs.k3s.io/architecture>`_
    - A server node is defined as a machine (bare-metal or virtual)
      running the ``k3s server`` command.
      A worker node is defined as a machine running the ``k3s agent`` command.

.. code-block:: sh

    curl -sfL https://get.k3s.io | K3S_TOKEN=SECRET sh -s - server --cluster-init
    curl -sfL https://get.k3s.io | K3S_TOKEN=SECRET sh -s - server --server https://<server1>:6443
    curl -sfL https://get.k3s.io | K3S_TOKEN=SECRET sh -s - server --server https://<server1>:6443


Using kubectl on Desktop
========================
* `k3s: Cluster Access <https://docs.k3s.io/cluster-access>`_

.. code-block:: sh

    scp root@<server1>:/etc/rancher/k3s/k3s.yaml ~/.kube/config
    vim ~/.kube/config  # change server: to <server1>


Contexts, Switching Clusters and Namespaces
===========================================
* `stepik k8s: 1.3 Устанавливаем Kubernetes локально <https://stepik.org/lesson/550144/step/3?unit=543781>`_
* `SO: What is the difference between namespaces and contexts in Kubernetes? <https://stackoverflow.com/questions/61171487/what-is-the-difference-between-namespaces-and-contexts-in-kubernetes>`_

Context - client connection parameters (cluster+user).

.. code-block:: sh

    kubectl config get-contexts                          # показать список контекстов
    kubectl config current-context                       # показать текущий контекст (current-context)
    kubectl config use-context my-cluster-name           # установить my-cluster-name как контекст по умолчанию

    kubectl --context default --namespace lesson14 get pods
    # or
    kubectl --context default get pods -n lesson14

    kubectl apply -f namespace.yaml
    # or kubectl create ns lesson14
    kubectl delete -f namespace.yaml

.. code-block:: yaml
    :caption: namespace.yaml

    apiVersion: v1
    kind: Namespace
    metadata:
      name: lesson14


Get information about k8s
=========================

.. code-block:: sh

    # also returns server version, so can be used to check connectivity
    kubectl version
    kubectl cluster-info

    # kubectl get - list resources
    # kubectl describe - show detailed information about a resource
    # kubectl logs - print the logs from a container in a pod
    # kubectl exec - execute a command on a container in a pod

    kubectl get pods
    kubectl get rs  # or: replicaset
    kubectl get deployments
    kubectl get nodes
    kubectl get pods -o wide
    kubectl get nodes -o wide

    kubectl get pod/redis configmap/example-redis-config
    kubectl get pods -l app=kubernetes-bootcamp
    kubectl get services
    kubectl get services -l app=kubernetes-bootcamp
    # Get pod's manifest
    kubectl -n lesson14 get pod/static-web -o yaml

    kubectl get --watch pods

    kubectl get events

    # "event" lists errors
    kubectl describe pods |grep Image
    kubectl describe pods
    kubectl describe services/kubernetes-bootcamp
    kubectl describe deployments
    kubectl describe deployments/kubernetes-bootcamp
    kubectl describe configmap/example-redis-config

    export POD_NAME=$(kubectl get pods -o go-template --template '{{range .items}}{{.metadata.name}}{{"\n"}}{{end}}')
    export NODE_PORT=$(kubectl get services/kubernetes-bootcamp -o go-template='{{(index .spec.ports 0).nodePort}}')

    kubectl logs $POD_NAME

    # Show pods CPU and memory usage
    # k3s: provided by API by deployment/metrics-server in kube-system namespace
    # (enabled by default)
    kubectl top pods


Labels and Annotations
======================
* `Kubernetes Annotations and Labels: What’s the Difference? <https://blog.getambassador.io/kubernetes-labels-vs-annotations-95fc47196b6d>`_
    - Labels are for Kubernetes, while annotations are for humans.
* `Best Practices Guide for Kubernetes Labels and Annotations <https://komodor.com/blog/best-practices-guide-for-kubernetes-labels-and-annotations/>`_

.. code-block:: sh

    kubectl get node srv1 -o json | jq .metadata.labels
    kubectl get node srv1 -o json | jq .metadata.annotations

    kubectl get node --selector kubernetes.io/hostname=srv1  # or -l

Annotations and labels syntax:

* key-value pairs
* Keys consists of two parts: an optional (but highly suggested) prefix and name
    - Prefix: DNS subdomain (<= 253 chars), ends with ``/``. E.g.: ``k8s.komodor.com/``
    - Name: required (<= 63 chars)
* if prefix is ommited, then label/annotation is private to the cluster+user

.. code-block:: yaml

    apiVersion: v1
    kind: Pod
    metadata:
      name: demo
      labels:
        environment: production
        app: nginx
      annotations:
         komodor.com/owner: alice
         komodor.com/owner-phone: 911
    spec:
      containers:
      - name: nginx
        image: nginx:1.14.2
        ports:
        - containerPort: 80


Configs and Secrets
===================
* `k8s: ConfigMaps <https://kubernetes.io/docs/concepts/configuration/configmap/>`_

.. code-block:: sh

    kubectl create configmap sys-app-name --from-literal name=my-system
                                        # --from-file
                                        # --from-env-file
    kubectl create secret generic sys-app-credentials --from-literal username=bob --from-literal password=bobpwd

    kubectl create cm test-config -n lesson16 --from-file=root-ca.pem


.. code-block:: yaml

    apiVersion: v1
    kind: ConfigMap
    metadata:
      name: first-cm
      namespace: lesson16
    data:
      config.yaml: |
        colorgood: purple
        colorbad: yellow
    ---
    # ...
          # in spec.containers.[]
          env:
            - name: COLORGOOD
              valueFrom:
                configMapKeyRef:
                  name: env-cm
                  key: colorgood
            - name: COLORBAD
              valueFrom:
                configMapKeyRef:
                  name: env-cm
                  key: colorbad
    --- # or
        # in spec.containers.[]
        volumeMounts:
          - name: cm-volume
            mountPath: "/etc/ssl/certs/"
            readOnly: true
    # in spec
    volumes:
      - name: cm-volume
        configMap:
          name: test-config


Volumes
=======

``emptyDir``: remains while the pod lives. Is a bit like ``/tmp``.
Also, it can be used for two container in one pod to share files.

.. code-block:: yaml

    spec:
      containers:
        - name: web
          image: ksxack/lesson1:v0.2
          ports:
            - containerPort: 8080
          volumeMounts:
            - name: cache-volume
              mountPath: /cache
      volumes:
        - name: cache-volume
          emptyDir: {}


Deployments and Scaling
=======================

.. code-block:: sh

    kubectl scale deployments/kubernetes-bootcamp --replicas=4
    kubectl scale deployments/kubernetes-bootcamp --replicas=2


Exec into the pod
=================

.. code-block:: sh

    kubectl exec $POD_NAME -- env
    kubectl exec -ti $POD_NAME -- bash
    # cat server.js
    # curl localhost:8080

    kubectl exec -ti $POD_NAME -- curl localhost:8080

    kubectl exec -it redis -- redis-cli
    # CONFIG GET maxmemory         --> 0
    # CONFIG GET maxmemory-policy  --> noeviction

    # Run new pod
    kubectl run -i --tty --image busybox:1.28 dns-test --restart=Never --rm


Copy files from/to Pod
======================

.. code-block:: sh

    kubectl cp {{namespace}}/{{podname}}:path/to/directory /local/path  # copy from pod
    kubectl cp /local/path namespace/podname:path/to/directory          # copy to pod


Port Forwarding
===============

.. code-block:: sh

    kubectl port-forward pods/mongo-75f59d57f4-4nd6q 28015:27017  # Проброс порта Пода
    kubectl port-forward mongo-75f59d57f4-4nd6q 28015:27017       # Проброс порта Сервиса

    kubectl port-forward -n lesson14 static-web 8080:80
    curl 127.0.0.1:8080


Services
========
* ` Kubernetes Service Types Explained <https://dev.to/pavanbelagatti/kubernetes-service-types-explained-207g>`_
* `K3s Load Balancing with Klipper <https://geek-cookbook.funkypenguin.co.nz/kubernetes/loadbalancer/k3s/>`_
* `k3s docs: networking: How the Service LB Works <https://docs.k3s.io/networking#how-the-service-lb-works>`_

Types of services:

* ClusterIP
    - makes pod available only from inside the cluster
* LoadBalancer
    - binds to the external IP
    - k3s servicelb
        + listens on every host, so only one service per port is possible
        + creates a pod (in ``kube-system`` namespace) on each node, which redirects (via iptables) traffic from this pod to service's IP and port
* NodePort
    - every node redirects the request to given port
    - only 30000–32767 ports available

.. code-block:: yaml

    # ClusterIP
    spec:
      ports:
        - protocol: TCP
          port: 80          # service port
          targetPort: 8080  # port in pod

    # LoadBalancer
    spec:
      type: LoadBalancer
      ports:
      - port: 80
        name: webport
        targetPort: 8080
      loadBalancerIP: 10.10.130.145

    # NodePort
    spec:
      type: NodePort
      ports:
      - name: http
        port: 80
        # targetPort: 8080
        nodePort: 30050
        protocol: TCP

Also can set ``externalIPs`` for ``type: ClusterIP`` service.


Deploy
======
* `How to use kubectl dry run <https://linuxhint.com/kubectl-dry-run/>`_
* `matchLabels, labels, and selectors explained in detail, for beginners <https://medium.com/@zwhitchcox/matchlabels-labels-and-selectors-explained-in-detail-for-beginners-d421bdd05362>`_
    - ``Why doesn’t the deployment automatically match the pod it’s deploying? I have no idea.``

Deployment is a kubernetes controller over ReplicaSet controller.
Other controllers are: DaemonSet and Job, CronJob:

* DaemonSet: creates one pod per node (like docker swarm's ``deploy.mode: global``)
    - use cases: promtail/fluentd, k8s-pinger/goldpinger
* Job: one-shot job. Starts pod, waits for it to finish, dies
* CronJob: run a job, scheduled

.. code-block:: sh

    kubectl apply -f redis-config.yaml --dry-run=server

    # Update image
    kubectl set image deployments/kubernetes-bootcamp kubernetes-bootcamp=jocatalin/kubernetes-bootcamp:v2
    curl 95.216.150.107:$NODE_PORT
    kubectl rollout status deployments/kubernetes-bootcamp

    kubectl rollout history deployment/goapp-deployment  # Проверить историю деплоймента
    kubectl rollout undo deployment/goapp-deployment     # Откатиться к предыдущей версии деплоймента
    kubectl rollout restart deployment/goapp-deployment  # Плавающий рестарт Подов в деплойменте

.. code-block:: yaml

    apiVersion: apps/v1
    kind: Deployment
    metadata:
      name: declarative-deployment
      labels:
        app: go-web
    spec:
      replicas: 1
      selector:
        matchLabels:
          app: goapp  # <-- to which pods this deployment is applied to
      template:  # <-- more like `podTemplate` starting here
        metadata:
          labels:
            app: goapp  # <-- pod's labels (usually same as matchLabels from above)
        spec:
          containers:
          - name: goapp
            image: ksxack/lesson1:v0.2
            ports:
            - containerPort: 8080


Log into private Registry
=========================
* `k8s: <https://kubernetes.io/docs/tasks/configure-pod-container/pull-image-private-registry/>`_

.. code-block:: sh

    # Based on existing credentials
    docker login ghcr.io  # --username <github-username> --password <password>
    kubectl create secret generic regcred --from-file=.dockerconfigjson=${PWD}/.docker/config.json --type=kubernetes.io/dockerconfigjson

    # Create anew
    kubectl create secret docker-registry regcred --docker-server=<your-registry-server> --docker-username=<your-name> --docker-password=<your-pword> --docker-email=<your-email>

    kubectl get secret regcred --output=yaml
    kubectl get secret regcred --output="jsonpath={.data.\.dockerconfigjson}" |base64 --decode

    # Then apply the pod below:
    kubectl apply -f private-reg-pod.yaml

.. code-block:: yaml
    :caption: private-reg-pod.yaml

    apiVersion: v1
    kind: Pod
    metadata:
      name: private-reg
    spec:
      containers:
      - name: private-reg-container
        image: <your-private-image>
      imagePullSecrets:
      - name: regcred


Helm
====
* `Grafana Helm Chart <https://github.com/grafana/helm-charts/blob/main/charts/grafana/README.md>`_
* `What Is Helm? A Quickstart Tutorial For Kubernetes Beginners <https://getbetterdevops.io/helm-quickstart-tutorial/>`_

Chart structure::

  test-chart
  ├── Chart.yaml
  ├── templates
  │  ├── deployment.yaml
  │  ├── secret.yaml
  │  └── service.yaml
  └── values.yaml

.. code-block:: yaml
    :caption: Chart.yaml

  apiVersion: v2
  name: test-chart
  description: A Helm chart for Kubernetes
  type: application
  version: 0.1.0
  appVersion: "1.16.0"

.. code-block:: yaml
    :caption: templates/secret.yaml

    apiVersion: v1
    kind: Secret
    metadata:
      name: {{ .Values.secret.name }}
    stringData:
      password: {{ .Values.secret.password }}

.. code-block:: yaml
    :caption: values.yaml

    image: nginx:latest
    replicas: 3
    secret:
      name: load-secret
      password: loadqwerty

.. code-block:: sh

  helm create test-chart
  # helm lint test-chart
  helm install my-helm-release test-chart -n tst-namespace -f test-chart/values.yaml --create-namespace
  helm uninstall -n tst-namespace my-helm-release

  helm install --debug --dry-run nginx nginx
  helm install my-release bitnami/nginx -f values.yaml

  helm repo add grafana https://grafana.github.io/helm-charts
  # helm search repo grafana
  # helm repo update
  helm install grafana grafana/grafana
  kubectl get pods -w
  kubectl get secret --namespace default grafana -o jsonpath="{.data.admin-password}" | base64 --decode ; echo
  export POD_NAME=$(kubectl get pods --namespace default -l "app.kubernetes.io/name=grafana,app.kubernetes.io/instance=grafana" -o jsonpath="{.items[0].metadata.name}")
  kubectl --namespace default port-forward $POD_NAME 3000

  helm install gabibbo97/gangway \
    --set config.apiServerURL='https://api.example.com:6443' \
    --set config.authorizeURL='https://auth.example.com/auth' \
    --set config.tokenURL='https://auth.example.com/token' \
    --set config.clientSecret='superSecret' \
    --set config.sessionSecurityKey='superSecure'


Requests, Limits
================

.. code-block:: yaml

  containers:
  - name: app
    image: ksxack/lesson1:v0.2
    resources:
      requests:   # how much pod wants to have (affects placement)
        memory: "100Mi"
        cpu: "200m"       # миллиядер CPU
      limits:     # how much pod can use, at max
        memory: "150Mi"
        cpu: "300m"

Quality of Service (QoS):

* Best Effort - такой класс присваивается, когда Вы вообще не указываете реквесты и лимиты;
* Burstable - данный класс будет присвоен, если лимиты и реквесты отличаются;
* Guaranted - когда лимиты и реквесты равны друг-другу.

По приоритету идут так Guaranted > Burstable > Best Effort.


Healthchecks (Probes)
============================
* `Configure Liveness, Readiness and Startup Probes <https://kubernetes.io/docs/tasks/configure-pod-container/configure-liveness-readiness-startup-probes/>`_


::

  startupProbe --> readinessProbe
               --> livenessProbe

.. code-block:: yaml
  :caption: livenessProbe

  apiVersion: v1
  kind: Pod
  metadata:
    labels:
      test: my-pod
    name: my-pod-http
  spec:
    containers:
    - name: containername
      image: k8s.gcr.io/liveness
      args:
      - /server
      livenessProbe:
        httpGet:
          path: /healthz
          port: 8080
          httpHeaders:
          - name: Custom-Header
            value: Awesome
        initialDelaySeconds: 3  # default: 0
        periodSeconds: 2        # default: 10
        # failureThreshold: 3   # default: 3
        # timeoutSeconds: 1
        # successThreshold: 1

.. code-block:: yaml
  :caption: readinessProbe

  readinessProbe:
    exec:
      command:
      - cat
      - /tmp/healthy
    initialDelaySeconds: 5
    periodSeconds: 5

.. code-block:: yaml
  :caption: startupProbe

  startupProbe:
    httpGet:
      path: /healthz
      port: liveness-port
    failureThreshold: 30
    periodSeconds: 10


Horizontal Pod Autoscaler
=========================

.. code-block:: yaml

  apiVersion: autoscaling/v2beta2
  kind: HorizontalPodAutoscaler
  metadata:
    name: php-apache
  spec:
    scaleTargetRef:
      apiVersion: apps/v1
      kind: Deployment
      name: php-apache
    minReplicas: 1
    maxReplicas: 5
    metrics:
    - type: Resource
      resource:
        name: cpu
        target:
          type: Utilization
          averageUtilization: 80

В данном примере, Делпойменту php-apache присуждается
минимальное количество реплик - 1,
максимальное - 5,
и в случае, если CPU у одного из Подов дойдет до 80% от реквеста,
то HPA добавит еще одну реплику.


Volumes
=======
* `SO: Kubernetes Persistent Volume Claim Indefinitely in Pending State <https://stackoverflow.com/questions/44891319/kubernetes-persistent-volume-claim-indefinitely-in-pending-state>`_

.. code-block:: sh

  docker run -d --net=host \
       --privileged --name nfs-server \
       katacoda/contained-nfs-server:centos7 \
       /exports/data-0001 /exports/data-0002

.. code-block:: yaml

  apiVersion: v1
  kind: PersistentVolume
  metadata:
    name: nfs-0002
  spec:
    capacity:
      storage: 5Gi
    accessModes:
      - ReadWriteOnce
      - ReadWriteMany
    persistentVolumeReclaimPolicy: Recycle
    nfs:
      server: 172.17.0.1
      path: /exports/data-0002

.. code-block:: yaml

  apiVersion: v1
  kind: PersistentVolumeClaim
  metadata:
    name: claim-http
  spec:
    storageClassName: ""  # <-- added to match the storage class of PV
    accessModes:
      - ReadWriteOnce
    resources:
      requests:
        storage: 1Gi


Other things
============

.. code-block:: sh

    GITHUB_URL=https://github.com/kubernetes/dashboard/releases
    VERSION_KUBE_DASHBOARD=$(curl -w '%{url_effective}' -I -L -s -S ${GITHUB_URL}/latest -o /dev/null | sed -e 's|.*/||')
    k3s kubectl create -f https://raw.githubusercontent.com/kubernetes/dashboard/${VERSION_KUBE_DASHBOARD}/aio/deploy/recommended.yaml

    kubectl create deployment kubernetes-bootcamp --image=gcr.io/google-samples/kubernetes-bootcamp:v1

    kubectl create deployment first-deployment  --image=ksxack/lesson1:v0.2
    kubectl edit ...  # just don't

    kubectl proxy &
    curl http://localhost:8001/version
    # fg
    # Ctrl+C

    curl http://localhost:8001/api/v1/namespaces/default/pods/$POD_NAME/

    kubectl expose deployment/kubernetes-bootcamp --type="NodePort" --port 8080

    curl 95.216.150.107:$NODE_PORT

    kubectl label pods $POD_NAME version=v1
    kubectl get pods -l version=v1

    kubectl delete service -l app=kubernetes-bootcamp
    curl 95.216.150.107:$NODE_PORT


    # kubectl create deployment node-hello --image=gcr.io/google-samples/node-hello:1.0 --port=8080
    # kubectl proxy --port=8080
    # curl http://localhost:8080/api/
    # curl http://localhost:8080/api/v1/namespaces/default/pods

    curl 95.216.150.107:$NODE_PORT
    curl 95.216.150.107:$NODE_PORT

    kubectl set image deployments/kubernetes-bootcamp kubernetes-bootcamp=jocatalin/kubernetes-bootcamp:v2
    curl 95.216.150.107:$NODE_PORT
    kubectl rollout status deployments/kubernetes-bootcamp

    kubectl set image deployments/kubernetes-bootcamp kubernetes-bootcamp=gcr.io/google-samples/kubernetes-bootcamp:v10
    kubectl rollout undo deployments/kubernetes-bootcamp

    cd sample-kubernetes-config/start/
    mvn package -pl system
    mvn package -pl inventory
    # https://kubernetes.io/docs/concepts/cluster-administration/manage-deployment/
    kubectl apply -f kubernetes.yaml
    kubectl wait --for=condition=ready pod -l app=inventory
    kubectl wait --for=condition=ready pod -l app=system
    curl -u bob:bobpwd http://$( minikube ip ):31000/system/properties
    curl http://$( minikube ip ):32000/inventory/systems/system-service
    curl -# -I -u bob:bobpwd -D - http://$( minikube ip ):31000/system/properties | grep -i ^X-App-Name:

    mvn package -pl system
    mvn package -pl inventory
    kubectl replace --force -f kubernetes.yaml

    curl -# -I -u bob:bobpwd -D - http://$( minikube ip ):31000/system/properties | grep -i ^X-App-Name:
    curl http://$( minikube ip ):32000/inventory/systems/system-service


    kubectl apply -f example-redis-config.yaml
    kubectl apply -f https://raw.githubusercontent.com/kubernetes/website/main/content/en/examples/pods/config/redis-pod.yaml

    kubectl apply -f example-redis-config.yaml

    kubectl delete pod redis
    kubectl apply -f https://raw.githubusercontent.com/kubernetes/website/main/content/en/examples/pods/config/redis-pod.yaml

    kubectl exec -it redis -- redis-cli

    kubectl delete pod/redis configmap/example-redis-config

Issues with official k8s tutorial:

* Some curl in the playground required -L (not mentioned in tutorial), while not requiring it for k3s installation
* Curling service behind proxy required a port number (8080) explicitly written (gist: https://gist.github.com/ipedrazas/403df2ed30ea8682e2b709ddc1c24bcf)
    - ``docker image pull gcr.io/google-samples/kubernetes-bootcamp:v1``
    - ``docker image inspect gcr.io/google-samples/kubernetes-bootcamp:v1``
* In module 4 ``kubectl label pods $POD_NAME version=v1`` in playground yields error message about label being already defined


K3s Hetzner Integration
=======================
* `How to set up K3S, GlusterFS and Hetzner's cloud load balancer <https://community.hetzner.com/tutorials/k3s-glusterfs-loadbalancer>`_
* `How to integrate k3s with a cloud controller <https://itnext.io/how-to-integrate-k3s-with-the-cloud-controller-36bd5020b8f7>`_
